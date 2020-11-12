#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(player, ok) {
    Player pl;
    Object_dynamic od;
    pl.take_elem(od);
    Point p;
    Speed s;
    pl.set_center(p);
    pl.set_speed(s);
    ASSERT_EQ(p.x, od.get_center().x);
    ASSERT_EQ(s.dx, od.get_speed().dx);
}