#pragma once
//
// COP0 register numbers.
//

// Registers used to identify the exception is marked with "Exc".
// Registers used to manipulate the TLB is marked with "TLB".
enum C0 {
	Index,    // TLB: TLB entry index to read and write to.
    Random,   // TLB: Random TLB index to read and write to.
    EntryLo0, // TLB: Read and write the "even" page mapped by the TLB.
    EntryLo1, // TLB: Read and write the "odd" page mapped by the TLB.
    Context,  // Exception:
    PageMask, // TLB: Holds the comparison mask that sets the page size for each TLB entry.
    Wired,    // TLB:

////////////////
	RESERVED1, 
////////////////

    BadVAddr, // Exception: Contains the virtual address that does not exist in the TLB.

    Count,    // Exception: Timer count.
    // The read/write Count register acts as a timer, 
    // incrementing at a constant rate—half the PClock speed—whether or not instructions are being executed. 
    // This register is a free-running type. When the register reaches all ones, it rolls over to zero and continues counting.


    EntryHi,  // TLB: used for reading and writing the high order bits of a TLB entry to the TLB MMU.

    Compare,  // Exception: Set the value to be compared with the Count register. When Compare-register equals to the Count-register, interrupt bit 7 in the Cause register is set. Writing to it clears the timer interrupt.
    // The Compare register is used to generate a timer interrupt.  It maintains a stable constant value that does not change on its own. 
    // When the value of the Compare register equals the value of the Count register (refer to 6.3.3), interrupt bit IP(7) in the Cause register is set. 
    // This causes an interrupt in the DF stage as soon as the interrupt is enabled. Writing a value to the Compare register, as a side effect, clears the timer interrupt.

    Status,   // Exception:
    Cause,    // Exception:
	EPC,      // Exception: The PC pointing to the instruction that caused the exception.
	PrevID,   // TLB:
	Config,
	LLAddr,
    WatchLo,
    WatchHi,
    C0_XContext,

//////////////////////////////////////////////////////////
    RESERVED2, RESERVED3, RESERVED4, RESERVED5, RESERVED6,
//////////////////////////////////////////////////////////

    PErr,
    CacheErr,
    TagLo,
    TagHi, 
    ErrorEPC, // Exception: PC for error exception. Contains the memory address where the program suspended and the exception occurred.

//////////////
    RESERVED7,
//////////////
};
