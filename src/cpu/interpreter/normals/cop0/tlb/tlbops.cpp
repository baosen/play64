#include "tlb.hpp"
#include "../../../err.hpp"
#include "../../../interp.hpp"
#include "../../../../../disassembler/strings.hpp"
#include <iostream>
using namespace System_control;

namespace {
	Entry ent() {
		Entry e = {0};

        // Virtual page number:
		e.mask = (cp0[PageMask] >> 13) & 0xfff;
		e.vpn2 = (cp0[EntryHi] >> 13) & 0x7ffff;
        e.g    = ((cp0[EntryLo1] & 1) & (cp0[EntryLo0] & 1)) != 0;

        // "Even" page.
        e.pfn0 = (cp0[EntryLo0] >> 6) & 0x3f;
        e.d0   = (cp0[EntryLo0] >> 2) & 1;
        e.v0   = (cp0[EntryLo0] >> 1) & 1;
        // "Odd" page.
		e.pfn1 = (cp0[EntryLo1] >> 6) & 0x3f;
        e.d1   = (cp0[EntryLo1] >> 2) & 1;
        e.v1   = (cp0[EntryLo1] >> 1) & 1;
		return e;
	}

//
// TLB instructions.
//

    // Read a TLB entry from the TLB cache.
    INSTR(tlbr) { // TLB Read.
        throw err("TLBR not implemented yet...");
    }

    // Write to an entry in the TLB indexed by COP0's INDEX-register.
    INSTR(tlbwi) { // TLB Write Index.
    	Tlb::set(cp0[Index] & 31, // Returns the 5-bit of the index-register.
                 ent());
    }
    
    // Write a TLB entry to a random index entry.
    INSTR(tlbwr) { // TLB Write Random.
    	Tlb::set(cp0[Random] % NENTRIES, ent());
    }

    // Probe TLB for matching entry (page. 146 in vr4300.pdf).
    INSTR(tlbp) { 
        throw err("TLBP not implemented yet..."); 
    }

    // Return from exception handler.
    INSTR(eret) { // Exception Return.
        // Is error bit set, meaning error exception was thrown?
    	if (System_control::get64(Status) & 4) {
            // Unset error bit.
    		System_control::cp0[Status] &= ~4;

            // Return to old PC before error.
    		Cpu::pc = cp0[ErrorEPC];
            return;
    	}
        // then exception bit is set.

        // Unset exception bit.
    	System_control::cp0[Status] &= ~2;

		// Return to old PC before exception.
    	Cpu::pc = cp0[EPC];
    }

    // Gets called when the interpreter interprets an unknown undefined TLB-instruction.
    INSTR(unktlb) { 
        throw err(undef("Tried to execute an unknown TLB-instruction: ", instr) + "!"); 
    }

    INSTRTBL(T) {
    	&unktlb,  &tlbr,    &tlbwi,    &unktlb, &unktlb, &unktlb, &tlbwr,    &unktlb,
    	&tlbp,    &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    	&unktlb,  &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    	&eret,    &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    	&unktlb,  &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    	&unktlb,  &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    	&unktlb,  &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    	&unktlb,  &unktlb,  &unktlb,   &unktlb, &unktlb, &unktlb, &unktlb,   &unktlb,
    };
}

INSTR(tlb) { T[instr.tlb()](instr); }
