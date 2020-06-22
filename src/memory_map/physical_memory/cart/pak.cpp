#include "pak.hpp"
#include "../../../cpu/interpreter/interp.hpp"
#include "../physmem.hpp"
#include "../sp/sp.hpp"
#include "../../byteswap.hpp"
#include "../../../cpu/interpreter/err.hpp"
#include <cassert>
#include <cstring>

namespace {
    // Is game cartridge ROM loaded?
    bool loaded = false;

    // Returns the length of a file.
    size_t len(FILE *fp, const char path[]) {
        // Is file opened and file path is not empty?
        assert(fp && path);

        // Get the file length of the opened file.
    	fseek(fp, 0L, SEEK_END);
    	const auto sz = ftell(fp);
        if (sz < 0)
            throw err(std::string("Failed to read length of file: ") + path);
    	rewind(fp);

    	// Return the size/length of the file in bytes.
    	return sz;
    }

    void close(FILE *fp, const char path[]) {
        assert(fp);
    	if (fclose(fp))
    		throw err(std::string("Failed to close ROM file: ") + path);
    }
}

enum {
    PAL = 0,  // 50 fps.
    NTSC = 1, // 60 fps.
    MPAL = 2, // 50 fps.
};

// Game cartridge (Game Pak).
namespace Pak {
	// The read-only memory in the Game Pak-cartridge.
    char rom[DOMAIN_SIZE] = {0}; // Cartridge Domain 1 Address 2.

    // Load ROM into memory.
    void load(const char path[]) {
        // Is not nullptr?
        assert(path);

        // Open ROM.
        const auto fp = fopen(path, "rb");
        if (!fp)
    		throw err(std::string("Failed to open file: ") + path);
        const auto l = len(fp, path);

        // Check if ROM is too large.
        if (l > DOMAIN_SIZE)
            throw err("ROM file is too large.");

        // Load ROM into the memory.
        if (fread(rom, 1, l, fp) <= 0) {
            close(fp, path);
    		throw err(std::string("Failed to read file: ") + path);
        }
        close(fp, path);

    	// Byteswap the entire rom to the correct endianness for the ROM in the Game Pak.
    	rombswap(rom, l);

        // Load boot code to Reality Signal Processor's Data Memory.
        memcpy(Sp::dmem+0x40, rom+0x40, 0xfc0);

        // Set TV-type.
        Physmem::wr32(0x300, NTSC);

        // Reset interpreter's state.
        Interpreter::reset();

        // Set cart is loaded!
        loaded = true;
    }

    // Read 32-bit value.
    u32 rd32(const u32 i) {
    	if (i > sizeof(rom)-1)
            throw err("Read outside ROM!");

    	return *rcast<u32*>(rom+i);
    }

    bool is_rom_loaded() {
        return loaded;
    }
}
