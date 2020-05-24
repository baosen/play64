#include "register.hpp"
#include "../instr.hpp"
#include "../err.hpp"
#include "cpu.hpp"
#include "../pc.hpp"

// Is always zero:
#define $zero Cpu::regs[zero]
// Reserved for assembler:
#define $at Cpu::regs[at]

// Stores results:
#define	$v0 Cpu::regs[v0]
#define $v1 Cpu::regs[v1]

// Stores arguments:
#define $a0	Cpu::regs[a0] 
#define $a1 Cpu::regs[a1] 
#define $a2 Cpu::regs[a2]
#define $a3 Cpu::regs[a3] 

#define $t0 Cpu::regs[t0]
#define $t2 Cpu::regs[t2]
#define $t3 Cpu::regs[t3]
#define $t4 Cpu::regs[t4]
#define $t5 Cpu::regs[t5]
#define $t6 Cpu::regs[t6]
#define $t7 Cpu::regs[t7]
#define $t8 Cpu::regs[t8]
#define $t9 Cpu::regs[t9]

#define $s6 Cpu::regs[s6]
#define $s7 Cpu::regs[s7]

// General purpose pointer?
#define $gp Cpu::regs[gp]
// Stores the stack pointer:
#define $sp Cpu::regs[sp]
// Stores the frame pointer:
#define $fp Cpu::regs[fp]

// Stores return address:
#define $ra Cpu::regs[ra]

namespace {
    memory_address old_pc = ENTRY_POINT;

	// Convert 64-bit value to 16-bit value.
    s16 c64to16(const s64 val) { return val & 0xffff; }
	// Convert 64-bit value to 32-bit value.
    s32 c64to32(const s64 val) { return val & 0xffffffff; }
	// Convert 32-bit value to 64-bit value.
    s64 c32to64(const s32 val) { return val & 0xffffffff; }
	// Convert 16-bit value to 64-bit value.
    s64 c16to64(const s16 val) { return val & 0xffff; }
	// Convert 8-bit value to 64-bit value.
    s64 c8to64(const unsigned int val) { return val & 0xff; }

    // Check if the caller is trying to access a register that does exist.
    void check(const u64 i) {
    	if (i > NREGS) throw err("Tried to access register > 32");
    }

	// Set the values that gets set before any CIC chip has executed.
    void precic()
	{
    	$a2 = 0xFFFFFFFFA4001F0CLL;
    	$a3 = 0xFFFFFFFFA4001F08LL;
    	$t0 = 0xC0LL;
    	$t2 = 0x40LL;
    	$t3 = 0xFFFFFFFFA4000040LL;
    	$sp = 0xFFFFFFFFA4001FF0LL;
    }

    // Set the values that gets set after an European CIC chip has executed.
    void posteucic()
	{
    	$s7 = 0x6LL;
    	$ra = 0xFFFFFFFFA4001554LL;
    }

	// Set the registers that the CIC 6102 sets after it has executed.
    void cic6102(const country_code code)
	{
    	$at = 0x1LL;
    	$v0 = 0xEBDA536LL;
    	$v1 = 0xEBDA536LL;
    	$a0 = 0xA536LL;
    	$t4 = 0xFFFFFFFFED10D0B3LL;
    	$t5 = 0x1402A4CCLL;
    	$t7 = 0x3103E121LL;
    	$s6 = 0x3FLL; // Checksum seed.
    	$t9 = 0xFFFFFFFF9DEBB54FLL;
    	switch (code) {
    	case country_code::Germany:
        case country_code::France:
    	case country_code::Italy:
    	case country_code::Europe:
        case country_code::Australia:
    	case country_code::PAL:
        case country_code::PAL_M:
    		$a1 = 0xFFFFFFFFC0F1D859LL;
    		$t6 = 0x2DE108EALL;
    		posteucic();
        default:
            break;
    	}
    }

	// Set the registers that the CIC 6103 sets after it has executed.
    void cic6103(const country_code code) {
    	$at = 0x1LL;
    	$v0 = 0x49A5EE96LL;
    	$v1 = 0x49A5EE96LL;
    	$a0 = 0xEE96LL;
    	$t4 = 0xFFFFFFFFCE9DFBF7LL;
    	$t5 = 0xFFFFFFFFCE9DFBF7LL;
    	$t7 = 0x18B63D28LL;
    	$s6 = 0x78LL;
    	$t9 = 0xFFFFFFFF825B21C9LL;
    	switch (code) {
    	case country_code::Germany:
        case country_code::France:
    	case country_code::Italy:
    	case country_code::Europe:
        case country_code::Australia:
    	case country_code::PAL:
        case country_code::PAL_M:
    		$a1 = 0xFFFFFFFFD4646273LL;
    		$t6 = 0x1AF99984LL;
    		posteucic();
        default:
            break;
    	}
    }

	// Set the registers that the CIC 6105 sets after it has executed.
    void cic6105(const country_code code) {
    	$v0 = 0xFFFFFFFFF58B0FBFLL;
    	$v1 = 0xFFFFFFFFF58B0FBFLL;
    	$a0 = 0xFBFLL;
    	$t4 = 0xFFFFFFFF9651F81ELL;
    	$t5 = 0x2D42AAC5LL;
    	$t7 = 0x56584D60LL;
    	$s6 = 0x91LL;
    	$t9 = 0xFFFFFFFFCDCE565FLL;
    	switch (code) {
    	case country_code::Germany:
        case country_code::France:
    	case country_code::Italy:
    	case country_code::Europe:
        case country_code::Australia:
    	case country_code::PAL:
        case country_code::PAL_M:
    		//*(u32 *)&pIMemBase[0x04] = 0xBDA807FC;
    		$a1 = 0xFFFFFFFFDECAAAD1LL;
    		$t6 = 0xCF85C13LL;
    		$t8 = 0x2LL;
    		posteucic();
        default:
            break;
    	}
    }

	// Set the registers that the CIC 6106 sets after it has executed.
    void cic6106(const country_code code) {
    	$v0 = 0xFFFFFFFFA95930A4LL;
    	$v1 = 0xFFFFFFFFA95930A4LL;
    	$a0 = 0x30A4LL;
    	$t4 = 0xFFFFFFFFBCB59510LL;
    	$t5 = 0xFFFFFFFFBCB59510LL;
    	$t7 = 0x7A3C07F4LL;
    	$s6 = 0x85LL;
    	$t9 = 0x465E3F72LL;
    	switch (code) {
    	case country_code::Germany:
        case country_code::France:
    	case country_code::Italy:
    	case country_code::Europe:
        case country_code::Australia:
    	case country_code::PAL:
        case country_code::PAL_M:
    		$a1 = 0xFFFFFFFFB04DC903LL;
    		$t6 = 0x1AF99984LL;
    		$t8 = 0x2LL;
    		posteucic();
        default:
            break;
    	}
    }

    // Emulates the PIF Boot ROM code, which is the entry code that gets executed when the Nintendo 64 powers on and resets. The code resides in a ROM in the PIF.
	// This function basically does the job the boot code in the PIF ROM does to the system. We don't execute the real PIF Boot ROM code in this emulator.
    void pifboot(const country_code code, // Specifies the specific PIF Boot code revision made for a specific country region. The boot code is contained in the PIF ROM installed onto the country region's hardware revision of the Nintendo 64 motherboard.
				 const Cic cic_type)	  // Which CIC-chip that the Game Pak (Cartridge) contains.
	{
    	// TODO: Need to copy crap to SP_IMEM for CIC-6105 boot.
    	//u8 * pIMemBase = (u8*)g_pMemoryBuffers[MEM_SP_MEM] + 0x1000;
    
    	precic();

        // Sets the registers as what the CIC security chips would set during the execution of the PIF boot rom code on reset.
    	switch (cic_type) {
    	case Cic::CIC_6101:
            $s6 = 0x3FLL;   // Checksum seed.
    		break;
    	case Cic::CIC_6102: // CIC-chip used by Mario 64.
    		cic6102(code);
    		break;
    	case Cic::CIC_6103:
    		cic6103(code);
    		break;
        case Cic::CIC_6105: // CIC-chip used by The Legend of Zelda: Ocarina of Time.
    		//*(u32*)&pIMemBase[0x00] = 0x3C0DBFC0;
    		//*(u32*)&pIMemBase[0x08] = 0x25AD07C0;
    		//*(u32*)&pIMemBase[0x0C] = 0x31080080;
    		//*(u32*)&pIMemBase[0x10] = 0x5500FFFC;
    		//*(u32*)&pIMemBase[0x14] = 0x3C0DBFC0;
    		//*(u32*)&pIMemBase[0x18] = 0x8DA80024;
    		//*(u32*)&pIMemBase[0x1C] = 0x3C0BB000;
    		cic6105(code);
    		break;
    	case Cic::CIC_6106:
    		cic6106(code);
    	}
    }

}

// The state of the Nintendo 64's MIPS CPU.
namespace Cpu {
	s64 regs[NREGS] = {0}; // General purpose registers that are 64-bit.
    s64 hi = 0,  	 	   // The HI-register.
        lo = 0;  	 	   // The LO-register.

// Program counter: Points to the next instruction to be executed.
// Can only be modified by branch and jump-instructions.
    memory_address pc = ENTRY_POINT;
// The program counter in my interpreter points to the next instruction,
// which does not follow the MIPS architecture standard, for simplicity.
// The original MIPS architecture has several parallel pipelines each containing a PC that points to the instruction it is currently executing.

    // Set the value in register i.
    void set64(const u64 i, const u64 val) {
    	check(i);
    	if (!i) 
            return;
    	regs[i] = val;
    }

    // Sets the lower 32-bits value of the register.
    // Zeroes the rest.
    void set32(const u64 i, const s32 val) {
    	check(i);
    	if (!i) 
            return;
    	regs[i] = c32to64(val);
    }

    // Sets the lower 32-bits value of the register.
    // Zeroes the rest.
    void set16(const u64 i, const Halfword val) {
    	check(i);
    	if (!i) 
            return;
        regs[i] = c16to64(val);
    }

    // Sets the lower 8-bits value of the register.
    // Zeroes the rest.
    void set8(const u64 i, const Byte val) {
    	check(i);
    	if (!i) 
            return;
        regs[i] = c8to64(val);
    }

    // Returns the value in register i.
    s64 get64(const uint i) {
    	check(i);
    	return regs[i];
    }

    // Returns the lower 32-bits value of the register.
    s32 get32(const uint i) {
    	check(i);
    	return c64to32(regs[i]);
    }
    
    // Returns the lower 16-bits value of the register.
    s16 get16(const uint i) {
    	check(i);
    	return c64to16(regs[i]);
    }

    s8 get8(const uint i) {
        return get64(i) & 0xff;
    }

    // Increment the program counter with a value e.g pc += value;
    void incpc(const s64 i) {
    	pc += i;
    }

    // Setup the registers like the PIF boot-code does to setup the hardware.
    void reset() {
    	pifboot(country_code::USA, Cic::CIC_6102);
    	pc = ENTRY_POINT;
    }
    
    // Advance the program counter with the size of one instruction (32-bit/4 bytes).
    void advance_program_counter() {
    	old_pc = pc;
    	pc += INSTR_SIZE;
    }
    
    // Revert to the old program counter-value used for internal debugging purposes.
    void revert() { 
        pc = old_pc;
    }
}
