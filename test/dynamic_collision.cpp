#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(dynamic_collision, ok) {
    Point p0 ={-1000,-1000,-1000};
    Size s0 = {0,0,0};
    Point p2 = {1000,1000,1000};
    Size s = {400,400,400};
    Point dyn_center_2 = {1100,1300,1000};
    glm::vec3 speed1 = {400,0,0};
    glm::vec3 speed2 ={-400,0,0};
    glm::vec3 camera = {1,0,0};
    auto elem = Object_dynamic(BALL, p2, s, speed1);
    auto elem2 = Object_dynamic(BALL, dyn_center_2, s, speed2);
    auto player = Player(p0, s0);

    std::list<Object_dynamic> dyn_elems;
    std::list<Object_static> stat_elems;
    std::list<Object_activated> act_elems;
    std::list<Object_activator> actr_elems;
    dyn_elems.push_back(elem);
    dyn_elems.push_back(elem2);

    auto el = dyn_elems.begin();
    el++;

    auto handler3 = Handler(dyn_elems,stat_elems,act_elems,actr_elems,player,camera);

    handler3.update(1,camera);

    ASSERT_LT(dyn_elems.begin()->get_speed().x, 380); //меньше начальной скорости минус сопротивление
    ASSERT_LT(dyn_elems.begin()->get_speed().y, 0); //отлетел вниз по y
    ASSERT_EQ(dyn_elems.begin()->get_speed().z, -980);

    ASSERT_GT(el->get_speed().x, -380); //меньше по модулю начальной скорости минус сопротивление
    ASSERT_GT(el->get_speed().y, 0); //отлетел вверх по y
    ASSERT_EQ(el->get_speed().z, -980);
}