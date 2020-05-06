#pragma once
#include "../../data_types/types.hpp"
#include "../memmacros.hpp"

#define SP_MEMSIZE 0x1000

namespace Sp {
    RD(mem_addr);
    WR(mem_addr);
    RD(dram_addr);
    WR(dram_addr);
    RD(rd_len);
    WR(rd_len); 
    RD(wr_len);
    WR(wr_len);
    RD(status);
    WR(status);
    RD(dma_full);
    RD(dma_busy);
    RD(semaphore);
    WRANY(semaphore);
    RD(ibist);

    extern char imem[SP_MEMSIZE];
    extern char dmem[SP_MEMSIZE];
    extern u32 pc;
};
