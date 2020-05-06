#pragma once
#include "../../data_types/types.hpp"

namespace RDram {
	extern char ram[];

    u32 rd32(const uint i);
    void wr32(const uint i, const u32 val);
}
