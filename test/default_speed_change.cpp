#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(default_speed_change, ok) {
    Point p0 ={-1000,-1000,-1000};
    Size s0 = {0,0,0};
    Point p2 = {1000,1000,1000};
    Point p1 = {100,100,100};
    Size s = {400,400,400};
    glm::vec3 sp = {10,10,10};
    glm::vec3 sp2 = {0,10,0};

    auto first = Object_dynamic(BALL, p2, s, sp);
    auto second = Object_dynamic(BALL, p1, s, sp2, true);

    std::list<Object_dynamic> dyn_elems;
    dyn_elems.push_back(first);
    dyn_elems.push_back(second);
    std::list<Object_static> stat_elems;
    std::list<Object_activated> act_elems;
    std::list<Object_activator> actr_elems;
    glm::vec3 camera = {1,0,0};
    auto player = Player(p0, s0);

    auto handler = Handler(dyn_elems, stat_elems, act_elems, actr_elems, player, camera);

    handler.update(1, camera);

    auto el = dyn_elems.begin();
    el++;
    glm::vec3 predicted_speed_1 = {0,0,-970};
    glm::vec3 predicted_speed_2 = {0,0,0};
    Point predicted_center_1 = {1010,1010,1010};
    Point predicted_center_2 = {100,110,100};

    ASSERT_EQ(dyn_elems.begin()->get_speed(), predicted_speed_1);
    ASSERT_EQ(el->get_speed(), predicted_speed_2);
    ASSERT_EQ(dyn_elems.begin()->get_center(), predicted_center_1);
    ASSERT_EQ(el->get_center(), predicted_center_2);

    handler.update(1, camera);

    predicted_speed_1 = {0,0,-1950};
    predicted_speed_2 = {0,0,0};
    predicted_center_1 = {1010,1010,40};

    ASSERT_EQ(dyn_elems.begin()->get_speed(), predicted_speed_1);
    ASSERT_EQ(el->get_speed(), predicted_speed_2);
    ASSERT_EQ(dyn_elems.begin()->get_center(), predicted_center_1);
    ASSERT_EQ(el->get_center(), predicted_center_2);
}