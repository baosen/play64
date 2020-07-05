#include <disassembler/strings.hpp>
#include <cpu/interpreter/sext.hpp>
#include <cpu/interpreter/registers/register.hpp>
#include <cpu/interpreter/interp.hpp>
#include <cpu/interpreter/registers/cpu.hpp>
#include <cpu/interpreter/err.hpp>
using namespace Interpreter;
using namespace Cpu;

namespace {
    auto shift(const int val) { return val << 2; }

    INSTR(bltz) {
        execute_instruction(fetch());
    	if (get32(instr.rs()) < 0) {
    		incpc(sext18(shift(instr.offset())));
    		return;
    	}
    	incpc(INSTR_SIZE);
    }
    // Branches are 32-bit in in 32-bit mode.
    INSTR(bgez) {
        execute_instruction(fetch()); // delay-slot execution.
    	if (get32(instr.rs()) >= 0) {
    		incpc(sext18(shift(instr.imm())));
    		return;
    	}
    	incpc(INSTR_SIZE); // jump over delay slot.
    }

    INSTR(bltzl) {
    	if (get32(instr.rs()) < 0) {
            execute_instruction(fetch());
    		incpc(sext18(shift(instr.offset())));
    	}
    }
    INSTR(bgezl) {
    	if (get32(instr.rs()) >= 0) {
            execute_instruction(fetch()); // delay-slot execution.
    		incpc(sext18(shift(instr.imm())));
    	}
    }
    INSTR(bltzal) {
    	set32(ra, Cpu::pc+4);
    	if (get32(instr.rs()) < 0) {
            execute_instruction(fetch());
    		incpc(sext18(shift(instr.offset())));
    		return;
    	}
        execute_instruction(fetch());
    	incpc(INSTR_SIZE);
    }
    INSTR(bgezal) {
    	set32(ra, Cpu::pc + 4);
    	if (get32(instr.rs()) >= get32(instr.rt())) {
            execute_instruction(fetch()); // delay-slot.
    		incpc(sext18(shift(instr.offset())));
    		return;
    	}
        execute_instruction(fetch()); // delay-slot.
    	incpc(INSTR_SIZE);
    }
    INSTR(bltzall) {
    	set32(ra, Cpu::pc + 4);
    	if (get64(instr.rs()) < 0) {
            execute_instruction(fetch());
    		incpc(sext18(shift(instr.offset())));
    	}
    }
    INSTR(bgezall) {
    	set32(ra, Cpu::pc + 4);
    	if (get32(instr.rs()) >= get32(instr.rt())) {
            execute_instruction(fetch()); // delay-slot.
    		incpc(sext18(shift(instr.offset())));
    	}
    }
    INSTR(unkreg) { throw err(undef("Unknown REGIMM-instruction: ", instr) + "!"); }

    INSTRTBL(regimms) {
    	&bltz,   &bgez,   &bltzl,   &bgezl,   &unkreg, &unkreg, &unkreg, &unkreg,
    	&unkreg, &unkreg, &unkreg,  &unkreg,  &unkreg, &unkreg, &unkreg, &unkreg,
    	&bltzal, &bgezal, &bltzall, &bgezall, &unkreg, &unkreg, &unkreg, &unkreg,
    	&unkreg, &unkreg, &unkreg,  &unkreg,  &unkreg, &unkreg, &unkreg, &unkreg,
    	&unkreg, &unkreg, &unkreg,  &unkreg,  &unkreg, &unkreg, &unkreg, &unkreg,
    	&unkreg, &unkreg, &unkreg,  &unkreg,  &unkreg, &unkreg, &unkreg, &unkreg,
    	&unkreg, &unkreg, &unkreg,  &unkreg,  &unkreg, &unkreg, &unkreg, &unkreg,
    	&unkreg, &unkreg, &unkreg,  &unkreg,  &unkreg, &unkreg, &unkreg, &unkreg,
    };
}

INSTR(regimm) { regimms[instr.regimm()](instr); }
