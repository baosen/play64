#include <iostream>
#include "../mi/mi.hpp"
using namespace std;

// SI: Serial interface
// Used to communicate via the PIF to the PIF's Boot ROM and the controller.

// SI DRAM address (R/W): [23:0] starting RDRAM address.
#define SI_DRAM_ADDR_REG SI_BASE_REG // R0: DRAM address.

// SI address read 64B (W): [] any write causes a 64B DMA write.
#define SI_PIF_ADDR_RD64B_REG (SI_BASE_REG+0x04) // R1: 64B PIF->DRAM.
// Address SI_BASE_REG + (0x08, 0x0c, 0x14) are reserved.

// SI address write 64B (W): [] any write causes a 64B DMA read.
#define SI_ADDRESS_WRITE 0x10
#define SI_PIF_ADDR_WR64B_REG (SI_BASE_REG+SI_ADDRESS_WRITE) // R4: 64B DRAM->PIF.

// Serial Interface offset:
#define STATUS_OFFSET 0x18
#define	DMA_BUSY      0x1
#define	RD_BUSY       0x2
#define	DMA_ERROR     0x8
#define	INTERRUPT     0x1000

namespace {
    u32 dramaddr  = 0, // DRAM memory address.
        stat      = 0, // SI Status.
        addrrd64b = 0, // PIF read 64 byte from address.
        addrwr64b = 0; // PIF write 64 byte to address.
}

// SI: Serial Interface.
// Interface to the controller and the PIF.
namespace Si {
    // DRAM memory address.
    RD(dram_addr) { 
        cout << "[SI] Read DRAM address." << endl;
        return dramaddr; 
    }
    WR(dram_addr) { 
        cout << "[SI] Write DRAM address." << endl;
        dramaddr = val; 
    }

    // Read 64 byte of the PIF memory address.
    WR(pif_addr_rd64b) {
        cout << "[SI] PIF address read 64 bytes." << endl;
    }
    // Write 64 byte of the PIF memory address.
    WR(pif_addr_wr64b) {
        cout << "[SI] PIF address write 64 bytes." << endl;
    }

    // Current status of the SI device.
    RD(status) {
        cout << "[SI] Read STATUS: " << hex << stat << endl;
        return stat;
    }
    // (R): [0]  DMA busy, 
    //      [1]  IO read busy, 
    //      [2]  reserved,
    //      [3]  DMA error, 
    //      [12] interrupt
    WR(status) {
        cout << "[SI] Clear SI interrupt." << endl;
        Mi::clearSI();
    }
    // (W): [] any write clears interrupt
}
