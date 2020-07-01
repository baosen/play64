#include "tlb.hpp"
#include "../../../registers/cpu.hpp"
#include "../../../err.hpp"
#include "../../cop0/syscon.hpp"
#include "../../../../../memory_map/mem.hpp"
#include "../../../../../memory_map/mips_exception_handlers.hpp"
#include <iomanip>

// TODO:
// - Global and valid bit.
namespace {
	std::array<Entry, NENTRIES> tlb_entries = {0}; // 56 pages is random and 8 is hard-wired.
    // Each TLB entry maps to a pair of pages (maps to two pages) called "Even" or "Odd", respectively, which is just names for the pages.
    // EntryLo0 is used to map "Even" pages. EntryLo1 is used map "Odd" pages.

    void dbgprint() {
        for (int i = 0; i < tlb_entries.size(); ++i)
            std::cout << std::hex << std::setw(8) << i << ": " << tlb_entries[i].vpn2 << std::endl;
    }
}

// Translation look-aside buffer used to cache mappings between
// virtual memory address to physical memory address.
namespace Tlb {
    // Reset the TLB table of entries.
    void reset() {
        // Zero out all TLB entries.
        zero(tlb_entries);
    }

    // Set the ith TLB entry in the table of TLB entries.
    void set(const uint i, const Entry& e) {
        if (i >= NENTRIES)
            throw err("TLB index out of range!");
        tlb_entries[i] = e;
    }

    // TODO: Maps a virtual address to a physical address.
    physical_memory_address map(const memory_address virtual_memory_address) {
        // Set the Virtual Address that was not found in the TLB.
        System_control::cp0[BadVAddr] = virtual_memory_address;

        // Set Virtual Page Number.
        System_control::cp0[EntryHi] = virtual_memory_address & 0xffffe000;

        // TODO: wtf?
        System_control::cp0[Context] = 0xff80000f | ((virtual_memory_address >> 9) & 0x7ffff0);

        // Jump to trap handler.
        if (System_control::cp0[Status] & 0x2)
            Cpu::pc = GENERAL_EXCEPTION_HANDLER;  // Jump to general exception handler.
        else if (virtual_memory_address >= 0x80000000 && virtual_memory_address < 0xc0000000)
            Cpu::pc = GENERAL_EXCEPTION_HANDLER;  // Jump to general exception handler.
        else
            Cpu::pc = TLB_MISS_TRAP_HANDLER; // Jump to TLB miss trap handler.

        // TODO: Used for debugging.
        throw err("Debug: Stop!");

        // Throw to unroll stack and indicate TLB miss.
        //throw Tlb::Miss();

        for (const auto& e : tlb_entries) {
            const auto vpn2 = (virtual_memory_address & 0x1FFFF000);
            if (vpn2 != e.vpn2)
                continue;
            throw err("Found TLB entry!");
        }
    }
}
