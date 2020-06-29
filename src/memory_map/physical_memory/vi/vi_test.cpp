#include <gtest/gtest.h>
#include "vi.hpp"

// Tests for the Video Interface (VI).

// TODO: Setup framebuffer.
// TODO: Teardown framebuffer.

// Allocate framebuffer and fill it.
TEST(vi, framebuffer_allocation) {
    // Allocate frame buffer.
    uint32_t framebuffer[640*480] = {0};

    // Set framebuffer address.

    // Fill framebuffer with the color red.

    // Check if framebuffer is filled with pixels.
    ASSERT_EQ(1, 1);
}