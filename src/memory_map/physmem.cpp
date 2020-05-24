#include <sstream>
#include "physmem.hpp"
#include "../cpu/interpreter/err.hpp"
#include "pak.hpp"
#include "rdram/rdram.hpp"
#include "pi/pi.hpp"
#include "ai/ai.hpp"
#include "si/si.hpp"
#include "ri/ri.hpp"
#include "vi/vi.hpp"
#include "mi/mi.hpp"
#include "sp/sp.hpp"
using namespace std;

// Exception-vectors: Memory addresses that the processor jumps to when an exception occurs.
// -----------------------------------------------------------------------------------------
// 0x80000000: bad virtual address (TLB miss).
// 0x80000080: bad 64bit virtual address, which you can't throw since most games run locked in 32bit address mode. (extended tlb miss).
// 0x80000100: cache miss.
// 0x80000180: general exception vector.

const size_t EXCEPTION_VECTOR_SIZE = 0x80;

// The video interface is write-only. It supports only DMA from RDRAM to a specific video buffer address 
// and allows you to change video modes and configurations.

// The audio interface is write-only. It connects to the Audio DAC. 
// It supports only DMA from RDRAM to a specific audio buffer address and allows you to set the audio frequency.

const size_t MEGABYTE = 1024 * 1000;

// http://level42.ca/projects/ultra64/Documentation/man/pro-man/pro08/index.html

#define MAP_READ_SINGLE(addr, ns, func) \
    else if (paddr == addr) \
        return ns::r_##func();
#define MAP_READ_SINGLE_VAR(addr, ns, var) \
    else if (paddr == addr) \
        return ns::var;
#define MAP_READ_SINGLE_CONSTANT(addr, constant) \
    else if (paddr == addr) \
        return constant;
#define MAP_READ_RANGE(start, size, ns, arr) \
    else if (start <= paddr && paddr < (start+size)) \
        return *(u32*)(ns::arr+(paddr-start));
#define MAP_READ_RANGE_CONSTANT(start, size, constant) \
    else if (start <= paddr && paddr < (start+size)) \
        return constant;
#define MAP_WRITE_SINGLE(addr, ns, func) \
    else if (paddr == addr) { \
        ns::w_##func(val); \
        return; \
    }
#define MAP_WRITE_ANY_SINGLE(addr, ns, func) \
    else if (paddr == addr) { \
        ns::w_##func(); \
        return; \
    }
#define MAP_WRITE_RANGE(start, size, ns, arr) \
    else if (start <= paddr && paddr < (start+size)) { \
        *(u32*)(ns::arr+(paddr-start)) = val; \
        return; \
    }

namespace RDregs {
    char regs[0xFFFFF] = {0};
}

namespace Pif {
    char pifram[0x1FC007FF-0x1FC007C0];
}

namespace Sram {
    u32 sram = 0;

    u32 r_sram() {
        return sram;
    }
}

// Physical memory.
// The CPU access all connected devices through this memory interface.
namespace Physmem {
    // Reads and returns the 32-bit word pointed by the given physical address.
    // - paddr: Physical memory address.
    u32 rd32(const memory_address paddr) {
        // Main random access memory storage (RDRAM):
	    if (paddr <= 0x3fffff)
            return *(u32*)(RDram::ram+paddr);
        if (0x400000 <= paddr && paddr <= 0x3EFFFFF)
            return 0;
        MAP_READ_RANGE(0x3f00000, 0xFFFFF, RDregs, regs)

        // Reality signal processor:
        // - Data memory:
        MAP_READ_RANGE(0x4000000, SP_MEMSIZE, Sp, dmem)
        // - Instruction memory:
        MAP_READ_RANGE(0x4001000, SP_MEMSIZE, Sp, imem)
        // - Program counter:
        MAP_READ_SINGLE(0x4080000, Sp, pc)

        // MIPS (MI) controller:
        MAP_READ_SINGLE(0x4300000, Mi, mode)
        // Version number of the MI controller:
        MAP_READ_SINGLE_CONSTANT(0x4300004, 0x01010101) // All parts are of version 1. Newer consoles use 0x02020202 for version 2.
        MAP_READ_SINGLE(0x4300008, Mi, intr)
        MAP_READ_SINGLE(0x430000C, Mi, intr_mask)

        // Video-interface (VI):
        MAP_READ_SINGLE(0x4400004, Vi, origin)

        MAP_READ_SINGLE(0x404001C, Sp, semaphore)
        MAP_READ_SINGLE(0x4040010, Sp, status)
        MAP_READ_SINGLE_VAR(0x4080000, Sp, pc)

        // Peripheral-interface (PI):
        MAP_READ_SINGLE(0x4600010, Pi, status)
        MAP_READ_SINGLE(0x4600014, Pi, bsd_dom1_lat)
        MAP_READ_SINGLE(0x4600018, Pi, bsd_dom1_pwd)
        MAP_READ_SINGLE(0x460001C, Pi, bsd_dom1_pgs)
        MAP_READ_SINGLE(0x4600020, Pi, bsd_dom1_rls)
        MAP_READ_SINGLE(0x4600024, Pi, bsd_dom2_lat)
        MAP_READ_SINGLE(0x4600028, Pi, bsd_dom2_pwd)
        MAP_READ_SINGLE(0x460002C, Pi, bsd_dom2_pgs)
        MAP_READ_SINGLE(0x4600030, Pi, bsd_dom2_rls)

        // RDram's interface (never emulated):
        MAP_READ_SINGLE(0x470000C, Ri, select)
        MAP_READ_SINGLE(0x4700010, Ri, refresh)

        // Serial interface (SI):
        MAP_READ_SINGLE(0x4800000, Si, dram_addr)
        MAP_READ_SINGLE(0x4800018, Si, status)

        // SRAM.
        MAP_READ_SINGLE(0x5000508, Sram, sram)

        // Game Pak (cartridge).
        MAP_READ_RANGE(0x10000000, DOMAIN_SIZE, Pak, rom)

        stringstream ss;
        ss << "Read to unknown physical address: 0x" << hex << paddr;
        throw err(ss.str());
    }

    // Reads and returns the 16-bit halfword pointed by the given physical address.
    u16 rd16(const memory_address paddr) {
        return rd32(paddr & (~3)) & 0xffff;
    }

    // Reads and returns the 8-bit byte pointed by the given physical address.
    u8 rd8(const memory_address paddr) {
        return rd32(paddr & (~3)) & 0xff;
    }

    void wr64(const memory_address paddr, const u64 val) {
        wr32(paddr, val & 0xffffffff);
        wr32(paddr+4, (val >> 32));
    }

    // Writes a 32-bit word to the given physical address.
    // - paddr: Physical memory address.
    // - val: 32-bit word value to write to the physical address given.
    void wr32(const memory_address paddr, const u32 val) {
        //
        // RDRAM
        //

        // RDram address range for its random access memory space:
	    if (paddr <= 0x3fffff) {
            *(u32*)(RDram::ram+paddr) = val;
            return;
        }

        // RDram's registers:
        MAP_WRITE_RANGE(0x3f00000, 0xFFFFF, RDregs, regs)
        MAP_WRITE_RANGE(0x4000000, SP_MEMSIZE, Sp, dmem)
        MAP_WRITE_RANGE(0x4001000, SP_MEMSIZE, Sp, imem)
        MAP_WRITE_ANY_SINGLE(0x404001C, Sp, semaphore)
        MAP_WRITE_SINGLE(0x4040010, Sp, status)

        //
        // Peripherals.
        //

        // The MIPS-controller interface between the CPU and the RCP.
        MAP_WRITE_SINGLE(0x4300000, Mi, mode)
        MAP_WRITE_SINGLE(0x430000C, Mi, intr_mask)

        // PIF (Joychannel) RAM inside the PIF-chip:
	    MAP_WRITE_RANGE(0x1FC007C0, 0x3F, Pif, pifram)

        // Video-interface:
        MAP_WRITE_SINGLE(0x4400000, Vi, control)
        MAP_WRITE_SINGLE(0x4400004, Vi, origin)
        MAP_WRITE_SINGLE(0x4400008, Vi, width)
        MAP_WRITE_SINGLE(0x440000C, Vi, intr)
        MAP_WRITE_SINGLE(0x4400010, Vi, current)
        MAP_WRITE_SINGLE(0x4400014, Vi, timing)
        MAP_WRITE_SINGLE(0x4400018, Vi, vsync)
        MAP_WRITE_SINGLE(0x440001C, Vi, hsync)
        MAP_WRITE_SINGLE(0x4400020, Vi, hsync_leap)
        MAP_WRITE_SINGLE(0x4400024, Vi, hstart)
        MAP_WRITE_SINGLE(0x4400028, Vi, vstart)
        MAP_WRITE_SINGLE(0x440002C, Vi, vburst)
        MAP_WRITE_SINGLE(0x4400030, Vi, xscale)
        MAP_WRITE_SINGLE(0x4400034, Vi, yscale)

        // Audio-interface:
        MAP_WRITE_SINGLE(0x4500008, Ai, control)
        MAP_WRITE_ANY_SINGLE(0x450000c, Ai, status)
        MAP_WRITE_SINGLE(0x4500010, Ai, dacrate)
        MAP_WRITE_SINGLE(0x4500014, Ai, bitrate)

        // Peripheral (PI) -interface:
        MAP_WRITE_SINGLE(0x4600000, Pi, dram_addr)
        MAP_WRITE_SINGLE(0x4600004, Pi, cart_addr)
        MAP_WRITE_SINGLE(0x4600008, Pi, rd_len)
        MAP_WRITE_SINGLE(0x460000C, Pi, wr_len)
        MAP_WRITE_SINGLE(0x4600010, Pi, status)
        MAP_WRITE_SINGLE(0x4600014, Pi, bsd_dom1_lat)
        MAP_WRITE_SINGLE(0x4600018, Pi, bsd_dom1_pwd)
        MAP_WRITE_SINGLE(0x460001C, Pi, bsd_dom1_pgs)
        MAP_WRITE_SINGLE(0x4600020, Pi, bsd_dom1_rls)
        MAP_WRITE_SINGLE(0x4600024, Pi, bsd_dom2_lat)
        MAP_WRITE_SINGLE(0x4600028, Pi, bsd_dom2_pwd)
        MAP_WRITE_SINGLE(0x460002C, Pi, bsd_dom2_pgs)
        MAP_WRITE_SINGLE(0x4600030, Pi, bsd_dom2_rls)

        // RDram-interface:
        MAP_WRITE_SINGLE(0x4700000, Ri, mode)
        MAP_WRITE_SINGLE(0x4700004, Ri, config)
        MAP_WRITE_SINGLE(0x4700008, Ri, current_load)
        MAP_WRITE_SINGLE(0x470000C, Ri, select)
        MAP_WRITE_SINGLE(0x4700010, Ri, refresh)
        MAP_WRITE_SINGLE(0x4700014, Ri, latency)
        MAP_WRITE_SINGLE(0x4700018, Ri, rerror)
        MAP_WRITE_SINGLE(0x470001C, Ri, werror)

        // Serial-interface:
        MAP_WRITE_SINGLE(0x4800018, Si, status)

        stringstream ss;
        ss << "Wrote " << hex << val << " to unknown physical address: 0x" << hex << paddr;
        throw err(ss.str());
    }

    // Writes a 16-bit halfword to the given physical address.
    void wr16(const memory_address paddr, const u16 val) {
        const auto addr = paddr & (~3);
        wr32(addr, (rd32(addr) & (~0xffff)) | val);
    }

    // Writes a 8-bit word to the given physical address.
    void wr8(const memory_address paddr, const u8 val) {
        const auto addr = paddr & (~3);
        wr32(addr, (rd32(addr) & (~0xff)) | val);
    }
}
