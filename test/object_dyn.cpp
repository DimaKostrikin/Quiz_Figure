#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(object_dyn, ok) {
    Point p;
    Speed s;
    Object_dynamic k = Object_dynamic(2, p, 10, s);
    ASSERT_EQ(s.dy, k.get_speed().dy);
    ASSERT_EQ(10, k.get_radius());
    Speed s1;
    k.set_speed(s1);
    k.set_radius(15);
    ASSERT_EQ(s1.dx, k.get_speed().dx);
    ASSERT_EQ(15, k.get_radius());
}