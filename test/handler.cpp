#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(handler, ok) {
    std::vector<Object_dynamic> od;
    std::vector<Object_static> os;
    std::vector<Object_activated> oa;
    Player pl;
    Point p;
    Speed s;
    Object_dynamic od1 = Object_dynamic(2, p, 10, s);
    od.push_back(od1);
    Point p1;
    Object_static os1 = Object_static(4, p1, 1, 2, 3);
    os.push_back(os1);
    Handler h = Handler(od, os, oa, pl);
    //Здесь в соответствии с заданными положениями объектов и скоростью, произойдет столкновение, проверяем
    //правильно ли хэндлер обработал коллизию
    h.updater();
    Point new_p;
    Speed new_s;
    ASSERT_EQ(new_p.x, od1.get_center().x);
    ASSERT_EQ(new_s.dx, od1.get_speed().dx);

}