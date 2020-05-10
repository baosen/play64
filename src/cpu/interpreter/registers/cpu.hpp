#pragma once
#include "../../../cartridge/ccode.hpp"
#include "../../../memory_map/memaddr.hpp"
#include "../../../data_types/types.hpp"

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
	s64 get64(const uint reg);
	s32 get32(const uint reg);
    s16 get16(const uint reg);
    s8  get8(const uint reg);

// Set register i to the value specified.
	void set64(const u64 i, const u64 val);
	void set32(const u64 i, const s32 val);
	void set16(const u64 i, const Halfword val);
    void set8(const u64 i, const Byte val);

// Increment program counter.
	void incpc(const s64 val);

// CPU registers:
	extern s64 regs[NREGS]; 
    extern s64 hi,     // SPECIAL HI register.
               lo;     // SPECIAL LO register.
    extern memory_address pc; // Program counter (instruction pointer):
}
