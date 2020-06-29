#pragma once
#include "../../memmacros.hpp"

// Video interface.
namespace Vi {
    // Controls the video output.
    WR(control);

    // The physical memory address to an allocated framebuffer.
    RD(origin);
    WR(origin);

    // The width of the framebuffer in pixels. How big is a pixel?
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
