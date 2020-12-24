#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(long_collision, ok) {
    Point p0 ={-1000,-1000,-1000};
    Size s0 = {0,0,0};
    Point p2 = {1000,1000,1000};
    Size s = {400,400,400};
    glm::vec3 spcol = {400,400,400};
    auto elem = Object_dynamic(BALL, p2, s, spcol);
    auto player = Player(p0, s0);
    glm::vec3 camera = {1,0,0};

    std::list<Object_dynamic> dyn_elems;
    dyn_elems.push_back(elem);

    Point wall_center = {1600, 1500, 1000};
    Size wall_size = {400, 1200, 5000};
    auto stat = Object_static(WALL, wall_center, wall_size);
    std::list<Object_static> stat_elems;
    std::list<Object_activated> act_elems;
    std::list<Object_activator> actr_elems;
    stat_elems.push_back(stat);

    auto handler = Handler(dyn_elems, stat_elems, act_elems, actr_elems, player, camera);

    handler.update(0.3, camera);

    ASSERT_LT(dyn_elems.begin()->get_center().x, 1200);//Удар по X. Максимально возможное реальное расстояние
    // между стеной и шаром 1600-400/2-400/2=1200

    handler.update(0.3,camera);

    ASSERT_GT(dyn_elems.begin()->get_center().x, 1200);//В этот момент шар "внутри", следующий шаг - коллизия

    handler.update(0.3,camera);

    ASSERT_LT(dyn_elems.begin()->get_center().x, 1200);//Произошел удар, шарик, отскочил от пов-сти стены
    ASSERT_LT(dyn_elems.begin()->get_speed().x, 0);//Скорость изменила свое направление после удара

}