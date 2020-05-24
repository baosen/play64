#pragma once

// Exception-vectors: Memory addresses that the processor jumps to when an exception occurs.
// -----------------------------------------------------------------------------------------
// 0x80000000: bad virtual address (TLB miss).
// 0x80000080: bad 64bit virtual address, which you can't throw since most games run locked in 32bit address mode. (extended tlb miss).
// 0x80000100: cache miss.
// 0x80000180: general exception vector.

#define EXCEPTION_VECTOR_SIZE 0x80

#define GENERAL_EXCEPTION_HANDLER  0x80000180 // Virtual address to the general exception handler.
#define TLB_MISS_TRAP_HANDLER 0x80000000 // Virtual address to the TLB miss trap handler.
