#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(static_collision, ok) {
    Point p0 ={-1000,-1000,-1000};
    Size s0 = {0,0,0};
    Point p2 = {1000,1000,1000};
    Size s = {400,400,400};
    glm::vec3 spcol = {200,200,200};
    auto elem = Object_dynamic(BALL, p2, s, spcol);

    std::list<Object_static> stat_elems;
    std::list<Object_activated> act_elems;
    std::list<Object_activator> actr_elems;
    glm::vec3 camera = {1,0,0};
    auto player = Player(p0, s0);

    std::list<Object_dynamic> dyn_elems;
    dyn_elems.push_back(elem);

    Point wall_center = {1380, 1500, 1000};
    Size wall_size = {400, 1200, 5000};
    auto stat = Object_static(WALL, wall_center, wall_size);
    stat_elems.push_back(stat);

    auto handler = Handler(dyn_elems, stat_elems, act_elems, actr_elems, player, camera);

    handler.update(1, camera);
    glm::vec3 predicted_speed = {-120, 180,-780}; //Vx=-(200*0.7 - 20(сопротивление воздуха) = -120
    Point predicted_center = {840, 1200,1200}; //Шар сначала "выйдет" из стены (x=980), затем переместится
    //(x=980 - 200*0.7 = 840)

    ASSERT_EQ(predicted_speed, dyn_elems.begin()->get_speed());
    ASSERT_EQ(predicted_center, dyn_elems.begin()->get_center());

    handler.update(1,camera);

    predicted_speed = {-100, 160, -1760};
    predicted_center = {720,1380,420};

    ASSERT_EQ(predicted_speed, dyn_elems.begin()->get_speed());
    ASSERT_EQ(predicted_center, dyn_elems.begin()->get_center());
}