#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(object, ok) {
    Point p;
    p.x = 1;
    p.y = 1;
    p.z = 1;
    Object k = Object(3, p);
    ASSERT_EQ(3, k.get_elem_type());
    ASSERT_EQ(p.x, k.get_center().x);
    Point p1;
    k.set_center(p1);
    ASSERT_EQ(p1.y, k.get_center().y);
}