#pragma once
#include "../../../data_types/types.hpp"

#define DOMAIN_SIZE 0x1ff00000

namespace Pak {
    extern char rom[]; // Cartridge Domain 1 Address 2. Contains the ROM data.

    // Load the file specified by path into the memory.
    void load(const char path[]);

    // Returns a reference to a modifiable 32-bit value from address at offset.
    u32 rd32(const u32 i);

    // Is game cartridge loaded.
    bool is_rom_loaded();
}
