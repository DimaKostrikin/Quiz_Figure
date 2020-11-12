#include "gtest/gtest.h"
#include "../include/features/feature_objects.h"

TEST(activator, ok) {
    std::vector<Object_dynamic> od;
    std::vector<Object_activator> obj_act_or;
    std::vector<Object_activated> obj_act_ed;
    Point p;
    Point door_p;

    p.x = 0;
    p.y = 1;
    p.z = 2;

    door_p.x = 100;
    door_p.y = 100;
    door_p.z = 0;

    int type_elem = 0;
    int type_door = 1;
    Object_activated door(type_door, door_p);
    obj_act_ed.push_back(door);

    Object_activator button(type_elem, p, &obj_act_ed[0]);

    Player player(p);

    Handler_feature hf(od, obj_act_or, player);

    EXPECT_EQ(obj_act_ed[0].is_activated(), true);


    ASSERT_EQ(1, 1);
}