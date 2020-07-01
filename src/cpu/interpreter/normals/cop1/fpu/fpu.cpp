#include "../../../../../data_types/types.hpp"
#include "../../../../../memory_map/mem.hpp"

#define NREGS 32

namespace {
	Dword regs[NREGS];
	Word ctrls[NREGS];
}

namespace Fpu {
    void reset() { 
        zero(regs); 
    }

    void set(const uint reg, const uint val) { 
        regs[reg] = val; 
    }

    void set_ctrl_reg(const uint reg, const Word val) { 
        ctrls[reg] = val; 
    }

    Dword get64(const uint i) { 
        return regs[i]; 
    }
}
