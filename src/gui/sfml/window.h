#pragma once

namespace gui { namespace sfml {
    // Create main window.
    void create_main_window();

    // Output 16-bit color image framebuffer to video output.
    void output_16bit_image(char framebuffer[]);

    // Output 32-bit color image framebuffer to video output.
    void output_32bit_image(char framebuffer[]);
}}