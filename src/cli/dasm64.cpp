#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include "../data_types/types.hpp"
#include "cmdparams.hpp"
#include "../cpu/interpreter/err.hpp"
#include "../disassembler/decode.hpp"
#include "../memory/byteswap.hpp"
using namespace std;

// Returns the length of a file that has been opened.
static size_t len(FILE *fp) {
    assert(fp);
	fseek(fp, 0L, SEEK_END);
	const auto sz = ftell(fp);
	rewind(fp);
	return sz;
}

// Load the ROM from the file path given.
// TODO: Check fclose for errors.
vector<u32> load(const char path[]) {
    // Open ROM.
    FILE* f = fopen(path, "r");
    if (!f)
        exit(EXIT_FAILURE);
    const size_t l = len(f);
    if (l % sizeof(u32) != 0) {
        fclose(f);
        exit(EXIT_FAILURE);
    }

    // Load ROM.
    vector<u32> rom(l/sizeof(u32));
    if (fread(rom.data(), 1, l, f) != l) {
        fclose(f);
        exit(EXIT_FAILURE);
    }
    fclose(f);
    rombswap(rom.data(), rom.size());

    return rom;
}

int main(const int argc, const char* argv[]) {
    // Parse given command-line arguments.
    int i = parse(argc, argv);
    if (i < 0) {
        error("No arguments provided!");
        return EXIT_FAILURE;
    }

    // Load ROM.
    auto rom = load(argv[i]);

    // Disassemble.
    int addr = 0;
    for (const auto& instr : rom) {
        cout << hex << addr << ": " << decode(instr) << endl;
        addr += 4;
    }

    return EXIT_SUCCESS;
}
