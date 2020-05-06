#include "../mi/mi.hpp"
#include "../rdram/rdram.hpp"
#include "../pak.hpp"
#include "../mem.hpp"
#include "../../logging/log.hpp"
#include <iostream>

// The DMA engine to DMA (copy asynchronously) data between RAM and game cartridge.
// Write the length and it begins the asynchronously DMA process automatically.
namespace {
    u32 dramaddr = 0, // RAM memory address.
        cartaddr = 0, // Cartridge memory address.
        rdlen    = 0, // Read from the Cartridge to RAM (Cartridge -> RAM).
        wrlen    = 0, // Write to RAM from Cartridge (RAM <- Cartridge).
        status   = 0; // DMA not busy at start.
}

// The Peripheral Interface (PI) is a 16-bit parallel bus connection to the the N64 Game Pak or the N64 Disk Drive.
// The PI uses DMA transfer to transfer information from the Game Pak or N64 Disk Drive to the RDRAM.
// The PI (Parallel Interface) is the DMA engine that connects the N64 Game Pak and/or the N64 Disk Drive to the RDRAM.
namespace Pi { //
    // TODO: Fit all registers into a global structure.
    void reset() {
        dramaddr = 0; // Source address to copy from.
        cartaddr = 0; // Destination address to copy to.
        rdlen    = 0; // Length to read from RAM to Cartridge.
        wrlen    = 0; // Length write from Cartridge to RAM.
        status   = 0; // Current status of the DMA copy operation.
    }

    WR(dram_addr) {
        std::cout << std::hex << "[PI] Setting physical RAM address: 0x" << val << std::endl;
        dramaddr = val;
    }

    WR(cart_addr) {
        std::cout << std::hex << "[PI] Setting physical cartridge address: 0x" << val << std::endl;
        cartaddr = val;
    }

    // Set the PI bit in the MI's interrupt register to indicate that the PI device has been interrupted by the processor.
    const unsigned int INT_PI = 0x10;

    // Length to read from RAM to Cartridge address space.
    // Used to copy data to a FLASH or SRAM stored on the cartridge.
    WR(rd_len) { // RAM -> Cartridge.
        std::cout << std::dec << "[PI] Reading from RAM to cartridge: " << val << "+1 bytes." << std::endl;

        // Copy from RAM to cartridge!
        rdlen = val;
        memcpy(Pak::rom                   // To ROM.
               + (cartaddr - 0x10000000), // Take 0x10000000 to map it to where the ROM data is stored on the host system.
               RDram::ram + dramaddr,     // From RAM.
               rdlen + 1);                // number of bytes + 1.

        // Signal that the PI is done with the DMA copy.
        Mi::interrupt(INT_PI);
    }

    // Length to write from Cartridge to RAM.
    // Used to copy data from the cartridge to the RAM.
    WR(wr_len) { // RAM <- Cartridge.
        std::cout << std::dec << "[PI] Writing from Cartridge to RAM: " << val << "+1 bytes." << std::endl;

        // TODO: Check if copying from Flash or SRAM to RAM.

        // Copy from ROM to RAM!
        wrlen = val;
        memcpy(RDram::ram + dramaddr,     // To RAM.
               Pak::rom                   // From the ROM in the Cartridge.
               + (cartaddr - 0x10000000), // Take 0x10000000 to map it to where the ROM data is stored on the host system.
               wrlen + 1);                // number of bytes + 1.

        // Signal that the PI is done with the DMA copy.
        Mi::interrupt(INT_PI);
    }

    RD(status) { 
        std::cout << std::hex << "[PI] Read STATUS: " << status << std::endl;
        return status; 
    }
    // (R) [0]: DMA busy 0/1 (true or false). 
    //     [1]: IO busy  0/1 (true or false). 
    //     [2]: Error    0/1 (true or false).

    WR(status) {
        // If program wants to reset the PI controller and abort current operation.
        if (val & 1) { // bit 1.
            std::cout << "[PI] Reset controller and abort current operation. " << std::endl;
            return; // TODO: Reset controller and abort current operation.
        }

        // Clear PI interrupt.
        if (val & 2) { // bit 2.
            std::cout << "[PI] Clear PI interrupt." << std::endl;
            Mi::clearPI();
        }
    }
    // (W): [0] Reset controller and abort current operation.
    //      [1] Clear PI interrupt.

// bao: I think this is to control cartridge clock cycles like Refresh rate etc...
// Control Cartridge Domain 1:
    RD(bsd_dom1_lat) { return 0; }
    RD(bsd_dom1_pwd) { return 0; }
    RD(bsd_dom1_pgs) { return 0; }
    RD(bsd_dom1_rls) { return 0; }
    WR(bsd_dom1_lat) {}
    WR(bsd_dom1_pwd) {}
    WR(bsd_dom1_pgs) {}
    WR(bsd_dom1_rls) {}

// Control Cartridge Domain 2:
    RD(bsd_dom2_lat) { return 0; }
    RD(bsd_dom2_pwd) { return 0; }
    RD(bsd_dom2_pgs) { return 0; }
    RD(bsd_dom2_rls) { return 0; }
    WR(bsd_dom2_lat) {}
    WR(bsd_dom2_pwd) {}
    WR(bsd_dom2_pgs) {}
    WR(bsd_dom2_rls) {}
}
