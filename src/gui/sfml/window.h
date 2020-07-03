#pragma once

namespace gui { namespace sfml {
    // Create main window.
    void create_main_window();

    // Set video resolution for the window.
    void set_video_resolution(const unsigned int horizontal_res, const unsigned int vertical_res);

    // Output 16-bit color image framebuffer to video output.
    void output_16bit_image(char framebuffer[]);

    // Output 32-bit color image framebuffer to video output.
    void output_32bit_image(char framebuffer[]);
}}