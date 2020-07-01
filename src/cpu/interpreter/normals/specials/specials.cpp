#include "../../interp.hpp"
#include "../../sext.hpp"
#include "../../../../disassembler/strings.hpp"
#include "../../err.hpp"
using namespace Cpu;
using namespace Interpreter;

namespace {
// Traps:
    INSTR(tne) { throw err("TNE not implemented yet..."); }
    INSTR(tge) { throw err("TGE not implemented yet..."); }
    INSTR(tgeu) { throw err("TGEU not implemented yet..."); }
    INSTR(tlt) { throw err("TLT not implemented yet..."); }
    INSTR(tltu) { throw err("TLTU not implemented yet..."); }
    INSTR(teq) { throw err("TEQ not implemented yet..."); }
    
// Doubleword shifts:
    INSTR(dsll) { throw err("DSLL not implemented yet..."); }
    INSTR(dsrl) { throw err("DSRL not implemented yet..."); }
    INSTR(dsra) { throw err("DSRA not implemented yet..."); }
    INSTR(dsllv) { throw err("DSLLV not implemented yet..."); }
    INSTR(dsrlv) { throw err("DSRLV not implemented yet..."); }
    INSTR(dsrav) { throw err("DSRAV not implemented yet..."); }
    
    INSTR(Break) { throw err("BREAK not implemented yet.."); }
    INSTR(sync) {} // All revisions of VR4300 executes SYNC as NOP.
    
    // Move register to HI.
    INSTR(mthi) { 
        hi = get64(instr.rs()); 
    }
    // Move register to LO.
    INSTR(mtlo) {
        lo = get64(instr.rs());
    }
    // Move from LO.
    INSTR(mflo) { 
        set64(instr.rd(), lo); 
    }
    // Move from HI.
    INSTR(mfhi) {
    	set64(instr.rd(), hi);
    }

    INSTR(addu) { 
        set64(instr.rd(), sext32((s32)get32(instr.rs())+(s32)get32(instr.rt()))); 
    }
    // TODO: Handle integer overflow.
    INSTR(add) { 
        addu(instr); 
    }

    INSTR(subu) { 
        set64(instr.rd(), sext32((s32)get32(instr.rs())-(s32)get32(instr.rt()))); 
    }
    // TODO: Implement "Integer Overflow-exception"
    INSTR(sub) { 
        subu(instr); 
    }

    INSTR(And) { 
        set64(instr.rd(), get64(instr.rs()) & get64(instr.rt())); 
    }
    INSTR(Or) { 
        set64(instr.rd(), get64(instr.rs()) | get64(instr.rt())); 
    }
    INSTR(nor) { 
        set64(instr.rd(), ~(get64(instr.rs()) | get64(instr.rt()))); 
    }
    INSTR(Xor) { 
        set64(instr.rd(), get64(instr.rs()) ^ get64(instr.rt())); 
    }

    // Set on less than unsigned.
    INSTR(sltu) {
    	if ((u64)get64(instr.rs()) < (u64)get64(instr.rt()))
    		set64(instr.rd(), 1);
    	else
    		set64(instr.rd(), 0);
    }

    // Set on less than signed.
    INSTR(slt) { 
    	if ((s64)get64(instr.rs()) < (s64)get64(instr.rt()))
    		set64(instr.rd(), 1);
    	else
    		set64(instr.rd(), 0);
    }

    // Doubleword add unsigned.
    INSTR(daddu) { 
        set64(instr.rd(), (s64)get64(instr.rs())+(s64)get64(instr.rt())); 
    }

    // Doubleword add.
    INSTR(dadd) {
        // TODO: Implement arithmethic overflow-exception.
        daddu(instr);
    }
    
    // Doubleword subtract unsigned.
    INSTR(dsubu) { 
        set64(instr.rd(), (s64)get64(instr.rs())-(s64)get64(instr.rt())); 
    }

    // Doubleword subtract.
    INSTR(dsub) {
        // TODO: Implement arithmethic overflow-exception.
        dsubu(instr);
    }
    
    // Doubleword shift left logical 32.
    INSTR(dsll32) { 
        set64(instr.rd(), (u64)get64(instr.rt()) << (u64)(instr.sa()+32)); 
    }
    // Doubleword shift right logical 32.
    INSTR(dsrl32) { 
        set64(instr.rd(), (u64)get64(instr.rt()) >> (u64)(instr.sa()+32)); 
    }
    // Doubleword shift right arithmethic 32.
    INSTR(dsra32) { 
        set64(instr.rd(), (s64)get64(instr.rt()) >> (s64)(instr.sa()+32)); 
    }

    // Multiply two signed values.
    INSTR(mult) {
        const s64 prod = (s64)sext32(get32(instr.rs()))*(s64)sext32(get32(instr.rt()));
        lo = sext32(prod & ~(u32)0);
        hi = sext32(prod >> 32);
    }    
    
    // Multiply two unsigned values.
    INSTR(multu){ 
        const u64 prod = (u64)get32(instr.rs())*(u64)get32(instr.rt());
        lo = sext32(prod & ~(u32)0);
        hi = sext32(prod >> 32);
    }

    // Division.
    INSTR(div) {
    	lo = rcast<int>(get32(instr.rs())) / rcast<int>(get32(instr.rt()));
    	hi = rcast<int>(get32(instr.rs())) % rcast<int>(get32(instr.rt()));
    }

    // Division unsigned.
    INSTR(divu) {
    	lo = scast<uint>(get32(instr.rs())) / scast<uint>(get32(instr.rt()));
    	hi = scast<uint>(get32(instr.rs())) % scast<uint>(get32(instr.rt()));
    }

    // TODO: Check for arithmetic overflow and raise exception for that.
    // Doubleword multiply.
    INSTR(dmult) {
        const __int128_t tmp = scast<__int128_t>(get64(instr.rt()))*scast<__int128_t>(get64(instr.rs()));
        lo = tmp & ~(u64)0;
        hi = tmp >> 64;
    }
    
    INSTR(dmultu) {
        const __uint128_t tmp = scast<__uint128_t>(get64(instr.rt()))*scast<__uint128_t>(get64(instr.rs()));
        lo = tmp & ~(u64)0;
        hi = tmp >> 64;
    }

    INSTR(ddiv) {
        lo = (get64(instr.rs()) / get64(instr.rt()));
        hi = (get64(instr.rs()) % get64(instr.rt()));
    }

    // Integer divides two 64-bit unsigned integers.
    INSTR(ddivu) {
        lo = (get64(instr.rs()) / get64(instr.rt()));
        hi = (get64(instr.rs()) % get64(instr.rt()));
    }

    // Shift word right arithmethic.
    INSTR(sra) { 
        set64(instr.rd(), sext32((s32)get32(instr.rt()) >> (s32)instr.sa())); 
    }
    // Shift word right logical.
    INSTR(srl) { 
        set64(instr.rd(), sext32(get32(instr.rt()) >> instr.sa())); 
    }
    // Shift word left logical.
    INSTR(sll) { 
        set64(instr.rd(), sext32(get32(instr.rt()) << instr.sa())); 
    }

    // Shift Right Logical Variable.
    INSTR(srlv) { 
        set64(instr.rd(), sext32((u32)get32(instr.rt()) >> (u32)(get32(instr.rs()) & 0x1f))); 
    }
    // Shift Right Arithmethic Variable.
    INSTR(srav) { 
        set64(instr.rd(), sext32((s32)get32(instr.rt()) >> (s32)(get32(instr.rs()) & 0x1f)));
    }
    // Shift Left Logical Variable.
    INSTR(sllv) { 
        set64(instr.rd(), sext32((u32)get32(instr.rt()) << (u32)(get32(instr.rs()) & 0x1f))); 
    }

    // Jump register.
    // - Jumps to the address pointed by the address in register rs.
    INSTR(jr) {
        execute_instruction(fetch()); // delay slot.
    	Cpu::pc = get32(instr.rs());
    }
    // Jump and link register.
    INSTR(jalr) { throw err("JALR is not implemented yet..."); }

    // System call.
    INSTR(syscall) { throw err("SYSCALL is not implemented yet.."); }

    INSTR(unkspec) { throw err(undef("Unknown SPECIAL-instruction: ", instr) + "!"); }

    INSTRTBL(specials) {
    	&sll,     &unkspec, &srl,     &sra,     &sllv,    &unkspec, &srlv,    &srav,
    	&jr,      &jalr,    &unkspec, &unkspec, &syscall, &Break,   &unkspec, &sync,
    	&mfhi,    &mthi,    &mflo,    &mtlo,    &dsllv,   &unkspec, &dsrlv,   &dsrav,
    	&mult,    &multu,   &div,     &divu,    &dmult,   &dmultu,  &ddiv,    &ddivu,
    	&add,     &addu,    &sub,     &subu,    &And,     &Or,      &Xor,     &nor,
    	&unkspec, &unkspec, &slt,     &sltu,    &dadd,    &daddu,   &dsub,    &dsubu,
    	&tge,     &tgeu,    &tlt,     &tltu,    &teq,     &unkspec, &tne,     &unkspec,
    	&dsll,    &unkspec, &dsrl,    &dsra,    &dsll32,  &unkspec, &dsrl32,  &dsra32
    };
}

INSTR(special) { 
    specials[instr.spec()](instr); 
}
