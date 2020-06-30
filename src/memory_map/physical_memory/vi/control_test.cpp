#include <gtest/gtest.h>
#include "control.h"

TEST(vi_control, set_control_register) {
    vi::control::set(1);
    ASSERT_EQ(vi::control::get(), 1);
}
