#include <cassert>
#include "../registers/register.hpp"
#include "../interp.hpp"
#include "../err.hpp"
#include "../../../memory_map/macros.hpp"
#include "../../../disassembler/strings.hpp"
#include "../sext.hpp"
using namespace std;
using namespace Cpu;
using namespace Interpreter;

INSTR(special);
INSTR(regimm);
INSTR(cop0);
INSTR(cop1);

namespace {
    auto idxsh(const Instr i) { 
        return i.instr_idx() << 2; 
    }
    auto offsh(const Instr i) { 
        return i.offset() << 2; 
    }

//
// Branches
//
    // Jump.
    INSTR(j) {
        execute_instruction(fetch());
    	pc = ((pc & 0xf8000000) | idxsh(instr));
    }
    // Jump and link.
    INSTR(jal) {
        execute_instruction(fetch());
    	set32(ra, pc + 4);
    	pc = (((pc + 4) & 0xf0000000) | idxsh(instr));
    }
    // Branch if equal.
    INSTR(beq) {
        // Fetch delay slot.
        const auto dslot = fetch();
        // Jump if equal.
    	if ((s32)get32(instr.rs()) == (s32)get32(instr.rt())) {
            // Execute delay slot.
            execute_instruction(dslot);
    		incpc(sext18(offsh(instr)));
    		return;
    	}
        // Execute delay slot.
        execute_instruction(dslot);
        // Jump over delay-slot.
    	incpc(INSTR_SIZE); 
    }
    // Branch not equal.
    INSTR(bne) {
        const auto dslot = fetch();
    	if ((s32)get32(instr.rs()) != (s32)get32(instr.rt())) {
            execute_instruction(dslot);
    		incpc(sext18(offsh(instr)));
    		return;
    	}
        execute_instruction(dslot);
    	incpc(INSTR_SIZE);
    }
    // Branch less than zero.
    INSTR(blez) {
        const auto dslot = fetch();
    	if ((s32)get32(instr.rs()) <= 0) {
            execute_instruction(dslot);
    		incpc(sext18(offsh(instr)));
    		return;
    	}
        execute_instruction(dslot);
    	incpc(INSTR_SIZE);
    }
    // Branch greater than zero.
    INSTR(bgtz) {
        const auto dslot = fetch();
    	if ((s32)get32(instr.rs()) > 0) {
            execute_instruction(dslot);
    		incpc(sext18(offsh(instr)));
    		return;
    	}
        execute_instruction(dslot);
    	incpc(INSTR_SIZE);
    }
    // Branch equal likely and execute delay slot if equal.
    INSTR(beql) {
    	if ((s32)get32(instr.rs()) == (s32)get32(instr.rt())) {
            execute_instruction(fetch());
    		incpc(sext18(offsh(instr)));
            return;
    	}
    	incpc(INSTR_SIZE);
    }
    // Branch not equal likely and execute delay slot if not equal.
    INSTR(bnel) {
    	if ((s32)get32(instr.rs()) != (s32)get32(instr.rt())) {
            execute_instruction(fetch());
    		incpc(sext18(offsh(instr)));
    		return;
    	}
    	incpc(INSTR_SIZE);
    }
    // Branch less or equal to zero likely and execute delay slot if true.
    INSTR(blezl) {
    	if ((s32)get32(instr.rs()) <= 0) {
            execute_instruction(fetch());
    		incpc(sext18(offsh(instr)));
    		return;
    	}
    	incpc(INSTR_SIZE);
    }
    // Branch greater than zero likely and execute delay slot if true.
    INSTR(bgtzl) {
    	if ((s32)get32(instr.rs()) > 0) {
            execute_instruction(fetch());
    		incpc(sext18(offsh(instr)));
    		return;
    	}
    	incpc(INSTR_SIZE);
    }

//
// Immediates
//
    // Add immediate unsigned.
    INSTR(addiu) { 
        set64(instr.rt(), sext32((s32)get32(instr.rs())+((s32)sext16(instr.imm()))&(~0))); 
    }
    // Add immediate.
    INSTR(addi) {
        addiu(instr);
        // Exceptions:
        // - Integer overflow.
    }

    // Set less than integer unsigned.
    INSTR(sltiu) {
    	if ((u64)get64(instr.rs()) < (u64)sext16(instr.imm())) // Unsigned comparison!
    		set64(instr.rt(), 1);
    	else
    		set64(instr.rt(), 0);
    }
    // Set less than integer.
    INSTR(slti) { 
    	if ((s64)get64(instr.rs()) < (s64)sext16(instr.imm())) // Signed comparison!
    		set64(instr.rt(), 1);
    	else
    		set64(instr.rt(), 0);
    }

    // AND immediate.
    INSTR(andi) { 
        set64(instr.rt(), get64(instr.rs()) & (instr.imm())); 
    }
    // OR immediate.
    INSTR(ori) { 
        set64(instr.rt(), get64(instr.rs()) | (instr.imm())); 
    }
    // XOR immediate.
    INSTR(xori) { 
        set64(instr.rt(), get64(instr.rs()) ^ (instr.imm())); 
    }

    // Doubleword add immediate unsigned.
    INSTR(daddiu) { 
    	set64(instr.rt(), (s64)get64(instr.rs())+sext16(instr.imm()));
    }
    // Doubleword add immediate.
    INSTR(daddi) {
        daddiu(instr);
        // TODO: Traps
        // - Trap on overflow.
    }

//
// Loads
//
    // Load upper immediate.
    INSTR(lui) { 
        set64(instr.rt(), sext32(instr.imm() << 16)); 
    }
    INSTR(ldl) { 
        throw err("LDL is not implemented yet..."); 
    }
    INSTR(ldr) { 
        throw err("LDR is not implemented yet..."); 
    }
    // Load signed 8-bit byte.
    INSTR(lb) {
    // TODO: Implement exceptions.
    	set64(instr.rt(), sext8(Vmem::rd8(VADDR)));
        // Exceptions:
        // - TLB Refill, TLB Invalid
        // - Address Error
    }
    // Load signed 16-bit halfword.
    INSTR(lh) {
        set64(instr.base(), sext16(Vmem::rd16(VADDR)));
    }
    // Load signed 32-bit word.
    INSTR(lw) {
    	set64(instr.rt(), sext32(Vmem::rd32(VADDR))); 
    }
    // Load 8-bit byte unsigned.
    INSTR(lbu) { 
        set8(instr.rt(), Vmem::rd8(VADDR)); 
    }
    // Load 16-bit halfword unsigned.
    INSTR(lhu) {
        set16(instr.base(), Vmem::rd16(VADDR));
    }
    // Load 32-bit word unsigned.
    INSTR(lwu) {
    	set32(instr.rt(), Vmem::rd32(VADDR));
    }
    INSTR(lwr) { 
        throw err("LWR is not implemented yet..."); 
    }
    INSTR(lwl) { 
        throw err("LWL is not implemented yet..."); 
    }

//
// Store
//
    // Store 8-bit byte.
    INSTR(sb) { 
        Vmem::wr8(VADDR, get8(instr.rt())); 
    }
    // Store 16-bit halfword.
    INSTR(sh) {
        Vmem::wr16(VADDR, get16(instr.rt()));
    }
    // Store 32-bit word.
    INSTR(sw) {
    	Vmem::wr32(VADDR, get32(instr.rt()));
    }
    // Store 64-bit doubleword:
    INSTR(sd) { 
        Vmem::wr64(VADDR, get64(instr.rt()));
        // Exceptions:
        // - TLB miss exception
        // - TLB invalid exception
        // - TLB modification exception
        // - Bus error exception
        // - Address error exception
        // - Reserved instruction exception (32-bit User or Supervisor mode)
    }

    INSTR(sdl) { throw err("SDL is not implemented yet..."); }
    INSTR(sdr) { throw err("SDR is not implemented yet..."); }
    INSTR(swr) { throw err("SWR is not implemented yet..."); }
    INSTR(swl) { throw err("SWL is not implemented yet..."); }

    // Controls the instruction- and data-cache between the CPU and memory.
    // TODO: Implement it some fine day.
    INSTR(cache) {}

    INSTR(ll) { 
        set64(instr.rt(), VADDR); 
    }
    INSTR(lwc1) { throw err("LWC1 is not implemented yet..."); }
    INSTR(lld) { throw err("LLD is not implemented yet..."); }

    // If FR = 1 (all 32 registers is enabled, not just 16 floating-point registers).
    bool isfr() {
        return ((System_control::get64(Status) >> 26) & 1) != 0;
    }

    // Load doubleword to floating-point coprocessor (COP 1).
    // TODO:
    // - Undefined LSB.
    // - Address exception.
    INSTR(ldc1) { 
        const auto k = VADDR;
        if (isfr()) { // page 165.
            Fpu::set(instr.rt(), k);
            return;
        }
        Fpu::set(instr.rt(), k & 0xffffffff);
        Fpu::set(instr.rt()+1, k >> 32);
    }

    // Load doubleword to coprocessor 2 (that does not exist on the Nintendo 64).
    INSTR(ldc2) { throw err("LDC2 is not implemented yet..."); }

    // Load doubleword.
    INSTR(ld) {
    	set64(instr.rt(), VADDR);
    }
    // Exceptions:
    // - TLB Refill, TLB Invalid,
    // - Bus error.
    // - Address Error.
    // - Reserved Instruction.
    // TODO:
    // - The low-order 3 bits must be zero. 
    //   If not, the result of the instruction is undefined.

    INSTR(sc) { throw err("SC is not implemented yet..."); }
    INSTR(swc1) { throw err("SWC1 is not implemented yet..."); }
    INSTR(scd) { throw err("SCD is not implemented yet..."); }
    INSTR(sdc1) { 
        if (isfr()) {
            Vmem::wr64(VADDR, Fpu::get64(instr.rt()));
            return;
        }
        Vmem::wr32(VADDR, Fpu::get64(instr.rt()));
        Vmem::wr32(VADDR+4, Fpu::get64(instr.rt()+1));
    }
    // Exceptions:
    // - Coprocessor unusable.
    // - TLB miss exception.
    // - TLB invalid exception.
    // - TLB modification exception.
    // - Bus error exception.
    // - Adderss error exception.
    INSTR(sdc2) { 
        throw err("SDC2 is not implemented yet..."); 
    }

    // Gets called when the interpreter interprets an unknown undefined instruction.
    INSTR(unk) { 
        throw err(undef("Unknown instruction: ", instr) + "!"); 
    }

    // A look-up table which the interpreter looks up the corresponding instruction to execute after
    // decoding an instruction from the binary.
    INSTRTBL(normals) {
    	&special, &regimm, &j,    &jal,   &beq,  &bne,  &blez,  &bgtz,
    	&addi,    &addiu,  &slti, &sltiu, &andi, &ori,  &xori,  &lui,
    	&cop0,    &cop1,   &unk,  &unk,   &beql, &bnel, &blezl, &bgtzl,
    	&daddi,   &daddiu, &ldl,  &ldr,   &unk,  &unk,  &unk,   &unk,
    	&lb,      &lh,     &lwl,  &lw,    &lbu,  &lhu,  &lwr,   &lwu,
    	&sb,      &sh,     &swl,  &sw,    &sdl,  &sdr,  &swr,   &cache,
    	&ll,      &lwc1,   &unk,  &unk,   &lld,  &ldc1, &ldc2,  &ld,
    	&sc,      &swc1,   &unk,  &unk,   &scd,  &sdc1, &sdc2,  &sd,
    };
}

namespace Normals {
    // Execute the related function for the opcode, which should manipulate the hardware's state.
    void call(const Instr i) {
    	assert(!i.is_nop()); // can't call this function with NOP-instructions.
    	normals[i.normal()](i);
    }
}
