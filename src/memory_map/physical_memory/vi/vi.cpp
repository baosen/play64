#include <iostream>
#include "vi.hpp"
#include "../mi/mi.hpp"
using namespace std;

#define NREGS 14

// This is the interface to control the Video-DAC (Video digital-to-analog converter).
namespace {
    Word line = 0;
    Word xscale = 1, yscale = 1; // is a fixed/float?
    Word fbaddr;
}

// Video DAC-interface.
namespace Vi {
    // Reset current line.
    void reset() { 
        line = 0;
    }

    // STATUS-register bit masks:
    enum {
        PIXEL_SIZE   = 0x3,
        GAMMA_DITHER = 0x4,
        DIVOT        = 0x8,
        SERRATE      = 0x40,
        ANTIALIAS    = 0x300
    };

// Controls the behaviour of the Video DAC/Encoder:
    WR(control) { // Sets the pixel-format of the framebuffer and how the pixels should be drawn.
        printf("[VI] Pixel size: %u bytes. Gamma-dither: %s. Divot: %s. Serrate: %s. Anti-alias: %s\n",
                val & PIXEL_SIZE, 
                val & GAMMA_DITHER ? "Enabled" : "Disabled", 
                val & DIVOT ? "Enabled" : "Disabled", 
                val & SERRATE ? "Enabled" : "Disabled", 
                val & ANTIALIAS ? "Enabled" : "Disabled");
    }

// Framebuffer origin DRAM address:
    RD(origin) {
        return fbaddr;
    }

// Sets the memory address of the currently used framebuffer.
// Usually used to implement double buffering.
    WR(origin) { // Framebuffer physical memory address that points to the origin.
        fbaddr = val;
        printf("[VI] Framebuffer-address: %08x\n", val);
    }

// Sets the width of the framebuffer in pixels.
    WR(width) { // horizontal width.
        printf("[VI] Framebuffer-width: %u pixels\n", val);
    }

// Assert an interrupt in combination with the MI when the Video DAC hits a certain line.
    WR(intr) { // interrupt.
        line = val; // on which line to interrupt.
    }

// Read the current half line the video DAC is working on.
    RD(current) {
        printf("[VI] Read current half line: %d\n", line);
        return line;
    }

// Clears asserted VI interrupt when written.
    WR(current) { // current vertical half line.
        Mi::clearVI();
    } 

// VI video timing.
    WR(timing) {
    }
// [7:0] horizontal sync width in pixels
// [15:8] color burst width in pixels
// [19:16] vertical sync width in half lines
// [29:20] start of color burst in pixels from h-sync

// Number of lines per frame in NTSC. Number of half-lines per field in PAL.
    WR(vsync) { 
        line = val;
        printf("[VI] Vertical sync set: %d lines\n", val);
    }

// Number of horizontal lines before horizontal retrace?
	WR(hsync) {
        printf("[VI] Horizontal sync set: %d pixels\n", val);
    }

// Horizontal sync leap.
	WR(hsync_leap) { // wtf?
    }

// Horizontal video start.
	WR(hstart) { // wtf?
        printf("[VI] Horizontal video start: %d pixel end: %d pixel\n", val >> 15, (val & 0x1ff));
    }
// (RW): [9:0] end of active video in screen pixels
//       [25:16] start of active video in screen pixels
    

// Vertical video start.
	WR(vstart) { 
        printf("[VI] Vertical video start: %d line end: %d line\n", val >> 15, (val & 0x1ff));
    }
// [9:0] end of active video in screen lines.
// [25:16] start of active video in screen lines.

// Vertical burst.
	WR(vburst) {
    }
// [9:0] end of color burst enable in half-lines.
// [25:16] start of color burst enable in half-lines.

// Horizontal (X) upscale.
	WR(xscale) {
        xscale = val;
    }
// Allows scaling the image up horizontally (in the X direction) to the required display format from a reduced number of rendered pixels per line

// Vertical (Y) upscale.
	WR(yscale) {
        yscale = val;
    }
// Allows scaling the image up vertically (in the Y direction) to the required display format from a reduced number of rendered lines per frame
}
