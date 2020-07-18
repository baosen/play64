#pragma once

void create_window(const char title[], const int width = 320, const int height = 240);

// N64 will output in 640x480 regardless of the fb resolution set.
void change_size(const unsigned int new_w, const unsigned int new_h);

// Draw framebuffer given. Format 5/5/5/1 (16-bit).
void draw16(const uint16_t fb[]);
