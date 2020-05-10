#include <iostream>
#include "sp.hpp"
using namespace std;

// The memory addresses to the devices connected to the address bus.
enum {
    DMEM = 0, /* RSP processor's data memory containing the task header. */
    // The task header is loaded in here.
    IMEM = 0x1000, /* RSP processor's instruction memory containing RSP instructions. */
    // The microcode is loaded in here.
    
    // Mapped to RSP COP0-registers.
    MEM_ADDR = 0x40000, // Master, SP memory address.
    DRAM_ADDR = 0x40004, // Slave, SP DRAM DMA address.
    RD_LEN = 0x40008, // SP read DMA length.
    WR_LEN = 0x4000C, // SP write DMA length.
    STATUS = 0x40010, // SP status.
    DMA_FULL = 0x40014, // SP DMA full.
    DMA_BUSY = 0x40018, // SP DMA busy.
    SEMAPHORE = 0x4001C, // SP semaphore (test and set).

    PC = 0x80000, // SP program counter.
    IBIST = 0x80004, // SP IMEM BIST.
};

// Signal processor, a scalar- and vector-processor.
namespace {
	s64 regs[32];  // Scalar-unit registers.
    u32 segid[16]; // The RSP can store and index 16 base addresses.
    // Base address[Segment ID] + Offset.
    // segid[0] is reserved (check manual).
    u32 reg[16]; // RSP COP0-registers that maps the DMA control. Maps RDP regs too.
    u32 memaddr = 0; // Data memory address (DRAM) or Instruction memory address (IMEM).
    u32 dramaddr = 0;
    // (RW): [23:0] RDRAM address.
    u32 rdlen = 0; // Read length (+1?) in bytes.
    // (RW): [11:0] length
    //       [19:12] count
    //       [31:20] skip                 
    //       direction: I/DMEM <- RDRAM
    u32 wrlen = 0; // Write length (+1?) in bytes.
    // (RW): [11:0] length
    //       [19:12] count
    //       [31:20] skip                 
    //       direction: I/DMEM -> RDRAM
    u32 stat = 1; // STATUS-register.
    u32 full = 0;
    u32 sema = 0;
    u32 bist = 0; // IMEM Built-In Self-Test.

    // TODO: Use the 16 segment addressing to physical address scheme...
}

// RSP memory callback functions mapped to the RSP's address space.
namespace Sp { 
    char imem[SP_MEMSIZE] = {0}, // Instruction memory.
         dmem[SP_MEMSIZE] = {0}; // Data memory.
    u32  pc = 0; // (RW): [11:0] SP's program counter.

// DMA read and write engine from the global RDRAM to the data (DMEM) or instruction (IMEM) memory of the RSP.

    // RDram memory address.
    RD(dram_addr) { 
        return dramaddr; 
    }
    WR(dram_addr) { 
        dramaddr = val; 
    }

    // RSP's data or instruction memory address.
    RD(mem_addr) { 
        return memaddr; 
    }
    WR(mem_addr) { 
        cout << hex << "[SP] Setting I/DMEM address: " << val << endl;
        memaddr = val; 
        throw 1;
    }
    // (RW): [11:0] DMEM or an IMEM offset.
    //       [12] 0 = DMEM memory address, 1 = IMEM memory address

    // Length in bytes to read from DRAM to I/DMEM.
    RD(rd_len) { // dram -> I/DMEM.
        return rdlen; 
    }
    WR(rd_len) { 
        cout << dec << "[SP] Setting RD_LEN: " << val << endl;
        rdlen = val;
        //memcpy(Pak::rom+(memaddr-0x10000000), , rdlen+1);
        throw 1;
    }

    // Length in bytes to write from I/DMEM to DRAM.
    RD(wr_len) { // dram <- I/DMEM.
        return wrlen; 
    }
    WR(wr_len) {
        wrlen = val;
        // TODO: Begin transmit.
        throw 1;
    }

    // Status of the Signal Processor and the DMA engine.
    RD(status) { 
        return stat; 
    }
    WR(status) { 
        stat = val; 
    }
    // (W): [0]  clear halt          (R): [0]  halt
    //      [1]  set halt                 [1]  broke
    //      [2]  clear broke              [2]  dma busy
    //      [3]  clear intr               [3]  dma full
    //      [4]  set intr                 [4]  io full
    //      [5]  clear single step        [5]  single step
    //      [6]  set sstep                [6]  interrupt on break
    //      [7]  clear intr on break
    //
    // User-defined signal bits that can be used to signal events between CPU and RSP:
    // (W):                           (R):
    //                                    [7]  read to check if signal 0 has been set.
    //      [8]  set intr on break        [8]  read to check if signal 1 has been set.
    //      [9]  clear signal 0           [9]  read to check if signal 2 has been set.
    //      [10] set signal 0             [10] read to check if signal 3 has been set.
    //      [11] clear signal 1           [11] read to check if signal 4 has been set.
    //      [12] set signal 1             [12] read to check if signal 5 has been set.
    //      [13] clear signal 2           [13] read to check if signal 6 has been set.
    //      [14] set signal 2             [14] read to check if signal 7 has been set.
    //      [15] clear signal 3
    //      [16] set signal 3
    //      [17] clear signal 4
    //      [18] set signal 4
    //      [19] clear signal 5
    //      [20] set signal 5
    //      [21] clear signal 6
    //      [22] set signal 6
    //      [23] clear signal 7
    //      [24] set signal 7

    RD(dma_full) { 
        return full; 
    }
    // (R): [0] valid bit, dma full.

    // Is the DMA engine busy copying?
    RD(dma_busy) { 
        return 0; // The DMA engine is never busy. This emulator transfers the data instantly after either read length or write length has been set up.
    }
    // (R): [0] valid bit, dma busy.

// Test and set bit acting as a lock for code that shares resources between CPU and SP.
    RD(semaphore) {
        // Set lock/semaphore.
        sema = 1;
        return sema;
    }
    WRANY(semaphore) {
        // Unlock semaphore.
        sema = 0; 
    }
    // (R): [0] semaphore flag (set on read). (W): [any bit] clear semaphore flag.

// Instruction memory's (IMEM) built-in self test.
    RD(bist) { 
        return bist; 
    }
    // (R): [0] BIST check.
    //      [1] BIST go.
    //      [2] BIST done.
    WR(bist) { 
        bist = val; 
    }
    // (W): [0] BIST check.
    //      [1] BIST go.
    //      [2] BIST clear.
}
