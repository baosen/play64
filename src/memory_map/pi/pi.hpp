#include "../../data_types/types.hpp"
#include "../memmacros.hpp"

// Parallel interface.
namespace Pi {
    WR(dram_addr);
    WR(cart_addr);
    WR(rd_len);
    WR(wr_len);
    RD(status);
    WR(status);

// bao: I think this is to control cartridge clock cycles.
// Refresh rate etc...
// Domain 1:
    RD(bsd_dom1_lat);
    RD(bsd_dom1_pwd);
    RD(bsd_dom1_pgs);
    RD(bsd_dom1_rls);
    WR(bsd_dom1_lat);
    WR(bsd_dom1_pwd);
    WR(bsd_dom1_pgs);
    WR(bsd_dom1_rls);
// Domain 2:
    RD(bsd_dom2_lat);
    RD(bsd_dom2_pwd);
    RD(bsd_dom2_pgs);
    RD(bsd_dom2_rls);
    WR(bsd_dom2_lat);
    WR(bsd_dom2_pwd);
    WR(bsd_dom2_pgs);
    WR(bsd_dom2_rls);
}
