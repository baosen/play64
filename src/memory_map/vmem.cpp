#include "../cpu/tlb/tlb.hpp"
#include "physmem.hpp"
#include "../cpu/interpreter/err.hpp"
#include <iomanip>

// MIPS virtual memory.
// --------------------
// The VR4300 supports the 32-bit virtual address spaces defined by MIPS:
// - KUSEG: Kernel user segment.
// - KSEG0: Kernel segment 0. Unmapped.
// - KSEG1: Kernel segment 1. Unmapped.
// - KSSEG/KSEG2: Kernel supervisor segment/segment 2.
// - KSEG3: Kernel segment 3.
// The 64-bit address space are not used by any Nintendo 64 games.

#define MAP_RANGE(begin, end, expr) \
    else if (begin <= vaddr && vaddr <= end) \
        return expr;

// Emulates the MIPS virtual/program address space executing in 32-bit mode (KX = 0 in STATUS-register is selected),
// which means that all memory addressing are in 32-bit.
namespace Vmem {
    // Converts a virtual address to a physical address.
    memory_address map(const memory_address vaddr) {
    	// KUSEG (Kernel user segment): 0x00000000 -> 0x7fffffff. User addressable space mapped by the TLB.
    	if (vaddr <= 0x7fffffff)
            return Tlb::map(vaddr);

        // TODO: Check if we are running in kernel mode.

        // 32-bit virtual addresses permitted when running in kernel mode.
    	MAP_RANGE(0x80000000, 0x9fffffff, vaddr & 0x1fffffff) // 0x8: KSEG0: Cached.   Kernel address space mapped to cached memory of physical address 0x00000000 - 0x7FFFFFFF.
    	MAP_RANGE(0xa0000000, 0xbfffffff, vaddr & 0x1fffffff) // 0xa: KSEG1: Uncached. Kernel address space directly mapped to physical address 0x00000000 - 0x7FFFFFFF.
        MAP_RANGE(0xc0000000, 0xffffffff, Tlb::map(vaddr))    // 0xc: KSSEG and KSEG3: TLB mapped.

        // Throw if accessing virtual address outside address space.
	    std::stringstream ss;
	    ss << "Unknown virtual address mapping: 0x" << std::hex << vaddr;
	    throw Vmem_err(ss.str());
    }

//
// Read memory functions.
//

    // Return the 32-bit word pointed by the given virtual address.
    u32 rd32(const memory_address vaddr) {
        return Physmem::rd32(map(vaddr));
    }

    // Return the 16-bit halfword pointed by the given virtual address.
    u16 rd16(const memory_address vaddr) {
        return Physmem::rd16(map(vaddr));
    }

    // Returns the 8-bit byte pointed by the given virtual address.
    u8 rd8(const memory_address paddr) {
        return Physmem::rd8(map(paddr));
    }

//
// Write memory functions.
//

    // Write a 64-bit value at the virtual address given.
    void wr64(const memory_address vaddr, u64 val) {
        Physmem::wr64(map(vaddr), val); 
    }

    // Write a 32-bit value at the virtual address given.
    void wr32(const memory_address vaddr, u32 val) {
        Physmem::wr32(map(vaddr), val); 
    }

    // Write a 16-bit value at the virtual address given.
    void wr16(const memory_address vaddr, u16 val) {
        Physmem::wr16(map(vaddr), val); 
    }

    // Write a 8-bit value at the virtual address given.
    void wr8(const memory_address vaddr, u8 val) {
        Physmem::wr8(map(vaddr), val); 
    }
}
