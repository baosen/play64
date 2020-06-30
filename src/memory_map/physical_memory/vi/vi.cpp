#include "vi.hpp"
#include "control.h"
#include "../mi/mi.hpp"
#include <cstdio>

// This is the interface to control the Video-DAC (Video digital-to-analog converter).
namespace {
    // VERTICAL START.
    Word vstart = 0;
    unsigned int get_vertical_start() {
        return (vstart >> 16) & 0x3ff;
    }
    unsigned int get_vertical_end() {
        return vstart & 0x3ff;
    }

    // HORIZONTAL START.
    Word hstart = 0;
    unsigned int get_horizontal_start() {
        return (hstart >> 16) & 0x3ff;
    }
    unsigned int get_horizontal_end() {
        return hstart & 0x3ff;
    }

    Word line = 0;
    Word xscale = 1, yscale = 1; // is a fixed/float?
    Word fbaddr = 0;
}

// The registers of the Video DAC-interface (VI).
namespace Vi {
    // Reset current line.
    void reset() {
        line = 0;
    }

    // Controls the behaviour of the Video DAC/Encoder:
    WR(control) { // Sets the pixel-format of the framebuffer and how the pixels should be drawn.
    /*
        printf("[VI] Pixel size: %u bytes. Gamma-dither: %s. Divot: %s. Serrate: %s. Anti-alias: %s\n",
                val & PIXEL_SIZE, 
                val & GAMMA_DITHER ? "Enabled" : "Disabled", 
                val & DIVOT ? "Enabled" : "Disabled", 
                val & SERRATE ? "Enabled" : "Disabled", 
                val & ANTIALIAS ? "Enabled" : "Disabled");
    */
        vi::control::set(val);
    }

    // Framebuffer origin DRAM address:
    RD(origin) {
        return fbaddr;
    }

    // Sets the memory address of the currently used framebuffer.
    // Can (and usually) used to implement double buffering.
    WR(origin) { // Framebuffer physical memory address that points to the origin.
        fbaddr = val;
        printf("[VI] Framebuffer-address: %08x\n", val);
    }

    // Sets the width of the framebuffer in number of pixels. 
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
        hstart = val;
    }
    // (RW): [9:0] end of active video in screen pixels
    //       [25:16] start of active video in screen pixels
    

    // Vertical video start.
	WR(vstart) { 
        vstart = val;
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
