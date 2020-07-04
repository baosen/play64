#include <cpu/interpreter/err.hpp>
#include "syscon.hpp"

static const int NUMBER_OF_COP0_REGISTERS = 32;

// MIPS System control co-processor (COP0).
// ---------------------------------------
// Controls the computer system. It is usually used by operating system software.
// This is where the TLB is stored and processed.
namespace System_control {
	Dword cp0[NUMBER_OF_COP0_REGISTERS];

	// Reset the coprocessor 0 registers to the initial values.
    void reset() {
        // Set the RANDOM-register to make the TLB Begin filling the 31st TLB entry.
	    cp0[Random]   = 31;
        cp0[Wired]    = 0; // specifies the boundary between Random and Wired entries.

        // Initialize the registers with the value the CIC-chip would set those registers to.
	    cp0[Count]    = 0x5000;
	    cp0[Cause]    = 0x5C;
	    cp0[EntryHi]  = 0xFFFFE0FF;
	    cp0[Context]  = 0x7FFFF0;
	    cp0[EPC]      = 0xFFFFFFFF;
	    cp0[BadVAddr] = 0xFFFFFFFF;
	    cp0[ErrorEPC] = 0xFFFFFFFF;
	    cp0[Status]   = 0x34000000;
	    cp0[Config]   = 0x6E463;
    }

    // Check if application software is trying to access an existing register.
    void inbounds(const uint i) {
    	if (i > NUMBER_OF_COP0_REGISTERS)
    		throw err("Trying to access COP0-register that does not exist!");
    }

	// Gets a coprocessor 0 register and return the 64-bit bits.
    Dword get64(const uint i) {
    	inbounds(i);

        switch (i) {
        case Wired:
            return cp0[i] & 0x1F; // only the five low-order bits are used.
        default:
            warn("Unknown COP0 register " + std::to_string(i) + " read!");
            return cp0[i];
        }
    }

	// Set a co-processor 0 register with a 64-bit value.
    void set64(const uint i, const Dword val) {
        // Check if accessing a valid register.
    	inbounds(i);

        // Set value to the register.
    	cp0[i] = val;

        // Do the side-effect action that gets executed when assigning values to the registers.
        switch (i) {
        case Wired:
            cp0[Random] = 31; // Writing this register also sets the Random register to the value of its upper bound of 31 (p. 150).
            break;
        case Compare:
            // TODO: Clear timer interrupt.
            break;
        default:
            warn("Unknown COP0 register " + std::to_string(i) + " set!");
            break;
        }
    }
    
    // Decrements the random register by 1.
    // The random register consist of a lower 6-bit string, where only the lower 5-bits of it are used for indexing the 32 TLB entries on the VR4300.
    void decrement_random() {
        cp0[Random] = ((cp0[Random] & 0x1f)-1) & 0x1f;
    }

    // TODO: Revert the control unit's state to the previous one.
    void revert() { 
        throw err("revert() is not implemented yet"); 
    }
}
