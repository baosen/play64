#include <gtest/gtest.h>
#include "control.h"

TEST(vi_control, set_control_register) {
    vi::control::set(1);
    ASSERT_EQ(vi::control::get(), 1);
}

TEST(vi_control, set_blank_tv_type) {
    vi::control::set(vi::control::blank);
    ASSERT_EQ(vi::control::get_tv_type(), vi::control::blank);
}

TEST(vi_control, set_nonsense_tv_type) {
    vi::control::set(0xf); // arbitrary value.
    ASSERT_EQ(vi::control::get_tv_type(), vi::control::rgba8888);

    vi::control::set(10); // arbitrary value.
    ASSERT_EQ(vi::control::get_tv_type(), vi::control::rgba5551);
}

TEST(vi_control, set_16_bit_color_type) {
    vi::control::set(vi::control::rgba5551);
    ASSERT_EQ(vi::control::get_tv_type(), vi::control::rgba5551);
}

TEST(vi_control, set_32_bit_color_type) {
    vi::control::set(vi::control::rgba8888);
    ASSERT_EQ(vi::control::get_tv_type(), vi::control::rgba8888);
}