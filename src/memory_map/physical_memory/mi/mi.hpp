#pragma once
#include "../../../data_types/types.hpp"
#include "../../memmacros.hpp"

// MIPS interface.
namespace Mi {
    void interrupt(const uint intbits);
    void intif();

    void clearSI();
    void clearAI();
    void clearVI();
    void clearPI();

    RD(mode);
    WR(mode);
    RD(intr);
    RD(intr_mask);
    WR(intr_mask);
}
