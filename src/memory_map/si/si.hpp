#include "../../data_types/types.hpp"
#include "../memmacros.hpp"

// Controller-interface. Combined with PIF.
namespace Si {
    RD(dram_addr); 
    WR(dram_addr); 
    RD(status);
    WR(status);
}
