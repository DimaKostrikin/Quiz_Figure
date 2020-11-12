#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(object_stat, ok) {
    Point p;
    Speed s;
    Object_static os = Object_static(4, p, 1, 2, 3);
    ASSERT_EQ(1, os.get_height());
    ASSERT_EQ(2, os.get_length());
    ASSERT_EQ(3, os.get_width());
}