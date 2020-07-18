#pragma once
#include "../../../../data_types/types.hpp"
#include "cop0const.hpp"

// The control processor for the MIPS architecture, known as Coprocessor 0 (COP0).
namespace System_control {
    extern Dword cp0[];

    // Reset system control.
    void  reset();

    // Get 64-bit value from COP0 register i.
	Dword get64(const unsigned int i);

    // Set 64-bit value from COP0 register i.
	void  set64(const unsigned int i, const Dword val);

    // Decrement random register.
    void  decrement_random();

    // Revert to previous state.
    void  revert();
}
