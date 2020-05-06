#include "../mem.hpp"
#include "ri.hpp"

// RDRAM interface (RI): Used to control the RDRAM behaviour.
// ----------------------------------------------------------
// This emulator only emulates reading and setting the values inside this address space.
// Other behaviours are currently not implemented and emulated.
namespace {
    u32 rimem[8]; // The registers to the RDRAM.
}

// 0x0470 0000 to 0x047F FFFF  RDRAM interface (RI) registers:
//     RI_BASE_REG - 0x04700000
namespace Ri {
// Reset the registers of the RDRAM to its initial state.
    void reset() { 
        zero(rimem); 
    }

// TODO: Read and write a range instead of single functions.

//  0x0470 0000 to 0x0470 0003  RI_MODE_REG
//           RI mode
    WR(mode) { 
        rimem[0] = val; 
    }
//     (RW): [1:0] operating mode
//           [2]   stop T active
//           [3]   stop R active


//  0x0470 0004 to 0x0470 0007  RI_CONFIG_REG
//           RI config
    WR(config) { 
        rimem[1] = val; 
    }
//     (RW): [5:0] current control input
//           [6]   current control enable

//  0x0470 0008 to 0x0470 000B  RI_CURRENT_LOAD_REG
//           RI current load
    WR(current_load) { 
        rimem[2] = val; 
    }
//      (W): [] any write updates current control register


//  0x0470 000C to 0x0470 000F  RI_SELECT_REG
//           RI select
    RD(select) { 
        return rimem[3]; 
    }
    WR(select) { 
        rimem[3] = val; 
    }
//     (RW): [2:0] receive select
//           [2:0] transmit select

//  0x0470 0010 to 0x0470 0013  RI_REFRESH_REG or RI_COUNT_REG
//           RI refresh
    RD(refresh) { 
        return rimem[4]; 
    }
    WR(refresh) { 
        rimem[4] = val; 
    }
//     (RW): [7:0]  clean refresh delay
//           [15:8] dirty refresh delay
//           [16]   refresh bank
//           [17]   refresh enable
//           [18]   refresh optimize

//  0x0470 0014 to 0x0470 0017  RI_LATENCY_REG
//           RI latency
    WR(latency) { 
        rimem[5] = val; 
    }
//     (RW): [3:0] DMA latency/overlap

//  0x0470 0018 to 0x0470 001B  RI_RERROR_REG
//           RI error
    WR(rerror) { 
        rimem[6] = val; 
    }
//      (R): [0] nack error
//           [1] ack error

//  0x0470 001C to 0x0470 001F  RI_WERROR_REG
//           RI error
    WR(werror) { 
        rimem[7] = val; 
    }
//      (W): [] any write clears all error bits
    
//  0x0470 0020 to 0x047F FFFF  Unused
}
