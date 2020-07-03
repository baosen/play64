#pragma once
#include "../../memory_map/memaddr.hpp"

namespace Dbg {
    bool has_user_set_any_breakpoints();
    bool breakstep();
    void bpset(const memory_address addr);
    void bprm(const memory_address addr);
    bool isbp(const memory_address addr);
}
