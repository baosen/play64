#include "control.h"

// VI's STATUS/CONTROL-register.
namespace {
    int32_t control = 0;

    unsigned int get_tv_type() {
        return control & 3;
    }

    // Check if gamma dither video output filter has been enabled by the game.
    bool is_gamma_dither_enabled() {
        return control >> 2 & 1;
    }

    // Check if gamma video output filter has been enabled by the game.
    bool is_gamma_enabled() {
        return control >> 3 & 1;
    }

    // Check if divot video output filter has been enabled by the game.
    bool is_divot_enabled() {
        return control >> 4 & 1;
    }

    // Check if game wants to enable the vbus clock.
    // This flag was introduced and used only on Ultra 64 prototypes.
    // Enabling it on the final hardware may permanently damage it.
    bool is_vbus_clock_enabled() {
        return control >> 5 & 1;
    }

    // Enable serrate filter on video output.
    bool serrate() {
        return control >> 6 & 1;
    }
}

namespace vi { namespace control {
    void set(int32_t value) {
        ::control = value;
    }
}}