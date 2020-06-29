#pragma once
#include "../../memmacros.hpp"

// Video interface.
namespace Vi {
    WR(control);
    RD(origin);
    WR(origin);
    WR(width);
    WR(intr);
    RD(current);
    WR(current);
    WR(timing);
    WR(vsync);
	WR(hsync);
	WR(hsync_leap);
	WR(hstart);
	WR(vstart);
	WR(vburst);
	WR(xscale);
	WR(yscale);
};
