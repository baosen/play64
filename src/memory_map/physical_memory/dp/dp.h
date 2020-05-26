#pragma once
#include "../../../data_types/types.hpp"
#include "../../memmacros.hpp"

// Reality Display Processor memory interface.
namespace Dp {
    RD(start);
    WR(start);

    RD(current);
    WR(current);

    RD(status);
    WR(status);

    RD(clock);
    WR(clock);

    RD(bufbusy);
    WR(bufbusy);

    RD(pipebusy);
    WR(pipebusy);

    RD(tmem);
    WR(tmem);

    RD(base);
    WR(base);

    RD(tbist);
    WR(tbist);

    RD(test_mode);
    WR(test_mode);

    RD(buftest_addr);
    WR(buftest_addr);

    RD(buftest_data);
    WR(buftest_data);
}
