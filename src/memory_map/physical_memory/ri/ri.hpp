#pragma once
#include "../../../data_types/types.hpp"
#include "../../memmacros.hpp"

namespace Ri {
    void reset();
    WR(mode);
    WR(config);
    WR(current_load);
    RD(select);
    WR(select);
    RD(refresh);
    WR(refresh);
    WR(latency);
    WR(rerror);
    WR(werror);
}
