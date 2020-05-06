#pragma once
#include "../../data_types/types.hpp"

namespace Fpu {
    void reset();
	void set(const uint reg, const uint val);
	void set_ctrl_reg(const uint reg, const Word value);
	Dword get64(const uint reg);
};
