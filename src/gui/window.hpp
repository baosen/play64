#pragma once
#include "../data_types/types.hpp"

void create_window(const char title[], const int width = 320, const int height = 240);
// N64 will output in 640x480 regardless of the fb resolution set.
void change_size(const uint new_w, const uint new_h);

// Draw framebuffer given. Format 5/5/5/1 (16-bit).
void draw16(const u16 fb[]);
