#pragma once
#include "../../../../data_types/types.hpp"
#include "cop0const.hpp"

// The control processor for the MIPS architecture, known as Coprocessor 0 (COP0).
namespace System_control {
    extern Dword cp0[];

    void  reset();
	Dword get64(const uint i);
	void  set64(const uint i, const Dword val);
    void  decrement_random();
    void  revert();
}
