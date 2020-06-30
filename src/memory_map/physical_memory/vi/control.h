#pragma once
#include <cstdint>

namespace vi { namespace control {
    enum tv_type {
        blank,
        reserved,
        rgba5551, // 16-bit color (internally 18-bit RGBA 5553).
        rgba8888, // 32-bit color.
    };

    int32_t get();
    unsigned int get_tv_type();

    void set(int32_t value);
}}