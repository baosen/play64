#include <disassembler/strings.hpp>
#include <cpu/interpreter/interp.hpp>
#include <cpu/interpreter/registers/cpu.hpp>
#include <cpu/interpreter/sext.hpp>
#include <cpu/interpreter/err.hpp>

// The floating-point unit.
namespace {
    INSTR(ctc1) { Fpu::set_ctrl_reg(instr.rd(), Cpu::get32(instr.rt())); } // rd == fs.
    INSTR(mtc1) { throw err("MTC1 is not implemented yet..."); }
    INSTR(cfc1) { Cpu::set64(instr.rt(), sext32(Fpu::get64(instr.rd()))); } // rd is same as fs.
    INSTR(mfc1) { Cpu::set64(instr.rt(), Fpu::get64(instr.rd())); } // rd same as fs.
    INSTR(unk) { throw err(undef("Tried to execute an unknown COP0 instruction: ", instr) + "!"); }
    INSTRTBL(Cop1) {
    	&mfc1, &unk, &cfc1, &unk, &mtc1, &unk, &ctc1, &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    	&unk,  &unk, &unk,  &unk, &unk,  &unk, &unk,  &unk,
    };
}

INSTR(cop1) { Cop1[instr.cop0()](instr); }
