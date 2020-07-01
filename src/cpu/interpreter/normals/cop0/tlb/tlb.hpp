#pragma once
#include "../../../../../memory_map/memaddr.hpp"
#include "../../../../../data_types/types.hpp"

// Each TLB entry is associated with a particular page size that is either 4096 bytes (4k pages) or 16 megabyte pages.
#define PAGE_NUMBER 0xfffff000
#define PAGE_OFFSET 0xfff

#define NENTRIES 32 // The CPU TLB consist of 32 entries, which provides mapping to 32 odd/even physical page pairs (64 total pages). 

// A TLB entry where 1 virtual page number points to 2 physical pages.
// 32 entries exists in COP0.
// The TLB registers stores parts of a single TLB entry.
struct Entry {
    Dword mask; // PageMask. Determines the page size. Either 4K or 16M pages.
    Dword vpn2; // "Virtual Page Number / 2", meaning the VPN points to 2 page frames.
    bool     g; // Global bit. If set, ASID is ignored.
    Dword asid; // Address space identifier. Used to identify a process in a OS.

    Dword pfn0; // Physical page frame address for the "Even" page.
    Dword c0;   // "Cache is used" bit.
    Dword d0;   // Dirty, meaning writeable. Functions as a "write-protect"-bit, not as a "written".
    Dword v0;   // Indicate if a page frame is valid. If not set, a TLB invalid exception (TLB or TLBS) occurs.

    Dword pfn1; // Physical page frame address for the "Odd" page.
    Dword c1;
    Dword d1;
    Dword v1;
};

typedef u32 physical_memory_address;

// Cache for address translations.
namespace Tlb {
    class Miss {};
    void reset();
    physical_memory_address map(const memory_address virtual_memory_address);
    void set(const uint i, const Entry& e);
};
