#include "control.h"

namespace {

// anamorphic NTSC resolution
namespace ntsc {
    const unsigned int width = 640;
    const unsigned int height = 480;
    const unsigned int vertical_sync = 525; // typical.
}

// anamorphic PAL resolution
namespace pal {
    const unsigned int width = 768;
    const unsigned int height = 576;
    const unsigned int vertical_sync = 625; // typical.
}

// VI's STATUS/CONTROL-register.
int32_t control = 0;

}

// STATUS-register bit masks:
enum {
    PIXEL_SIZE   = 0x3,
    GAMMA_DITHER = 0x4,
    DIVOT        = 0x8,
    SERRATE      = 0x40,
    ANTIALIAS    = 0x300
};

namespace vi { namespace control {
    unsigned int get_tv_type() {
        return ::control & 3;
    }

    // Check if gamma dither video output filter has been enabled by the game.
    bool is_gamma_dither_enabled() {
        return ::control >> 2 & 1;
    }

    // Check if gamma video output filter has been enabled by the game.
    bool is_gamma_enabled() {
        return ::control >> 3 & 1;
    }

    // Check if divot video output filter has been enabled by the game.
    bool is_divot_enabled() {
        return ::control >> 4 & 1;
    }

    // Check if game wants to enable the vbus clock.
    // This flag was introduced and used only on Ultra 64 prototypes.
    // Enabling it on the final hardware may permanently damage it.
    bool is_vbus_clock_enabled() {
        return ::control >> 5 & 1;
    }

    // Enable serrate filter on video output.
    bool serrate() {
        return ::control >> 6 & 1;
    }

    void set(int32_t value) {
        ::control = value;
    }

    int32_t get() {
        return ::control;
    }
}}