#include "gtest/gtest.h"
#include "physics_interface/classes.h"

TEST(player_dyn_collision, ok) {
    Point p2 = {1000,1000,1000};
    Size s = {400,400,400};
    glm::vec3 spcol = {200,200,200};
    glm::vec3 camera = {1,0,0};
    auto elem = Object_dynamic(BALL, p2, s, spcol);

    std::list<Object_dynamic> dyn_elems;
    std::list<Object_static> stat_elems;
    std::list<Object_activated> act_elems;
    std::list<Object_activator> actr_elems;
    dyn_elems.push_back(elem);

    Point player_center = {1100,1300,1000};
    Size player_size = {400,400,5000};
    auto pl1 = Player(player_center, player_size);

    auto handler = Handler(dyn_elems, stat_elems, act_elems, actr_elems, pl1, camera);

    handler.update(1,camera);

    glm::vec3 predicted_speed = {180, -120,-780};//коллизия по y; Vy=-(200*0.7 - 20)
    Point predicted_center = {1200,760,1200};//сначала "выталкиваем" объект, затем меняем координату
    //1300 - 200 - 200 = 900; 900-(200*0,7) = 760

    ASSERT_EQ(predicted_speed, dyn_elems.begin()->get_speed());
    ASSERT_EQ(predicted_center, dyn_elems.begin()->get_center());

    handler.update(1,camera);

    predicted_speed = {160,-100,-1760};
    predicted_center = {1380,640,420};

    ASSERT_EQ(predicted_speed, dyn_elems.begin()->get_speed());
    ASSERT_EQ(predicted_center, dyn_elems.begin()->get_center());
}