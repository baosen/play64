#pragma once
#include "../../../data_types/types.hpp"
#include "../../memmacros.hpp"

// Audio interface.
namespace Ai {    
    WR(dram_addr);
    WR(len);
    WR(control);
    RD(status);
    WRANY(status);
    WR(dacrate);
    WR(bitrate);
}
