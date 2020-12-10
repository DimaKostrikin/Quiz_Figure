#include "gtest/gtest.h"
#include "../include/Objects/Objects.h"
#include "../include/Logic_manager/Logic_manager.h"
#include "../include/Handler_feature/Handler_feature.h"

TEST(activator, open_door_by_pressed_button) {
    Point point1 = {0, 0, 0};
    Point point2 = {0, 10, 0};
    Size size1 = {0, 0, 0};
    Speed speed1 = {0, 1000, 0};
    Player player(point1, size1);
    std::list<Object_dynamic> obj_dyn;
    std::list<Object_activator> obj_actor;
    std::list<Object_activated> obj_acted;
    std::list<Object_influence> obj_infl;

    obj_dyn.emplace_back(Object_dynamic(CUBE, point1, size1, speed1));


    obj_acted.emplace_back(Object_activated(DOOR, point1, size1));

    obj_actor.emplace_back(Object_activator(BUTTON, point2, size1, obj_acted.front()));


    auto &Hand_feat = Handler_feature::instance(obj_acted, obj_actor, obj_dyn, obj_infl, player);


    Hand_feat.do_logic();

    EXPECT_EQ(obj_acted.front().is_activated(), false);

    auto it_dyn = obj_dyn.begin();
    std::cout << it_dyn->get_center();
    it_dyn->update_position();
    std::cout << it_dyn->get_center();
    Hand_feat.do_logic();
    std::cout << obj_acted.front().is_activated() << std::endl;
    EXPECT_EQ(obj_acted.front().is_activated(), true);
    it_dyn++;
    it_dyn->update_position();
    std::cout << it_dyn->get_center();
    Hand_feat.do_logic();
    EXPECT_EQ(obj_acted.front().is_activated(), false);

}