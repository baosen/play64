#include "../../interp.hpp"
#include "../../../../disassembler/strings.hpp"
#include "../../err.hpp"

INSTR(tlb);

// The control processor, also known as co-processor 0, for the MIPS computer architecture.
namespace {
    // Move to COP0.
    INSTR(mtc0) { 
        System_control::set64(instr.rd(), Cpu::get64(instr.rt()));
    }
    // Move from COP0.
    INSTR(mfc0) { 
        Cpu::set64(instr.rt(), System_control::get64(instr.rd()));
    }
    // Gets called when the interpreter interprets an unknown undefined instruction.
    INSTR(unk) { 
        throw err(undef("Tried to execute an unknown COP0 instruction: ", instr) + "!"); 
    }
    // The instructions for the control unit.
    INSTRTBL(Cop0) {
    	&mfc0, &unk, &unk, &unk, &mtc0, &unk, &unk, &unk,
    	&unk, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    	&tlb, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    	&unk, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    	&unk, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    	&unk, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    	&unk, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    	&unk, &unk, &unk, &unk, &unk, &unk, &unk, &unk,
    };
}

INSTR(cop0) { Cop0[instr.cop0()](instr); }
