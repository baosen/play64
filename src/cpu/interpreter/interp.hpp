#pragma once
#include "../interpreter/normals/cop0/syscon.hpp"
#include "../interpreter/normals/cop1/fpu/fpu.hpp"
#include "registers/cpu.hpp"
#include "../../cartridge/ccode.hpp"
#include "instr.hpp"
#include "../../memory_map/virtual_memory/vmem.hpp"
#include "../../disassembler/disassembly.hpp"
#include "../interpreter/normals/cop0/tlb/tblsize.hpp"

// Defines a MIPS instruction.
#define INSTR(name) void name(const Instr instr)

// Instruction table.
#define INSTRTBL(name) const instr_t name[NDEFINSTR]

typedef void (*instr_t)(const Instr);

// An interpreter that interprets MIPS instructions.
// A MIPS III-processor can have at most 3 coprocessors.
namespace Interpreter {
    // Fetch an instruction.
    Instr fetch();
    // Execute MIPS instruction.
    void execute_instruction(const Instr instruction);
	// Load N64 rom from a specified file path.
	void load(const char filepath[]);
	// Reset system. 
	void reset();
	// Execute one single instruction from where the PC points to.
	void step();
}
