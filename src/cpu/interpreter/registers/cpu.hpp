#pragma once
#include "../../../cartridge/ccode.hpp"
#include "../../../memory_map/memaddr.hpp"

#define NREGS 32 // The number of registers in the VR4300 MIPS III cpu.

enum class Cic {
	CIC_6101,
	CIC_6102,
	CIC_6103,
	CIC_6105,
	CIC_6106,
};

namespace Cpu {
// Initialize registers with start values.
	void reset();
// Advance the program counter.
	void advance_program_counter();
// Revert the processors state one step backwards.
	void revert();

// Returns the content of GPR i.
	int64_t get64(const uint reg);
	int32_t get32(const uint reg);
    int16_t get16(const uint reg);
    int8_t  get8(const uint reg);

// Set register i to the value specified.
	void set64(const uint64_t i, const uint64_t val);
	void set32(const uint64_t i, const int32_t val);
	void set16(const uint64_t i, const int16_t val);
    void set8(const uint64_t i, const uint8_t val);

// Increment program counter.
	void incpc(const s64 val);

// CPU registers:
	extern s64 regs[NREGS]; 
    extern s64 hi,     // SPECIAL HI register.
               lo;     // SPECIAL LO register.
    extern memory_address pc; // Program counter (instruction pointer):
}
