#include "classes.h"

int main() {
    Point p0 ={0,0,0};
    Size s0 = {0,0,0};
    Point p2 = {1000,1000,1000};
    Point p1 = {100,100,100};
    Size s = {400,400,400};
    glm::vec3 sp = {10,10,10};
    glm::vec3 sp2 = {0,10,10};
    glm::vec3 spcol = {200,200,200};

    auto first = Object_dynamic(BALL, p2, s, sp);
    auto second = Object_dynamic(BALL, p1, s, sp2, true);

    std::vector<Object_dynamic> dyn_elems;
    dyn_elems.push_back(first);
    dyn_elems.push_back(second);
    std::vector<Object_static> stat_elems;
    std::vector<Object_activated> act_elems;
    std::vector<Object_activator> actr_elems;
    glm::vec3 camera = {1,0,0};

    std::cout << "first ";
    print_speed(dyn_elems[0].get_speed());
    std::cout << "second ";
    print_speed(dyn_elems[1].get_speed());

    std::cout << "first " << dyn_elems[0].get_center();
    std::cout << "second " << dyn_elems[1].get_center();


    auto player = Player(p0, s0);
    std::cout << "Player " << player.get_center();
    auto handler = Handler(dyn_elems, stat_elems, act_elems, actr_elems, player, camera);

    handler.update(1, camera);

    std::cout << std::endl << "one second gone:" << std::endl << std::endl;

    std::cout << "first ";
    print_speed(dyn_elems[0].get_speed());
    std::cout << "second ";
    print_speed(dyn_elems[1].get_speed());

    std::cout << "first " << dyn_elems[0].get_center();
    std::cout << "second " << dyn_elems[1].get_center();

    handler.update(1, camera);

    std::cout << std::endl << "two seconds gone:" << std::endl << std::endl;

    std::cout << "first ";
    print_speed(dyn_elems[0].get_speed());
    std::cout << "second ";
    print_speed(dyn_elems[1].get_speed());

    std::cout << "first " << dyn_elems[0].get_center();
    std::cout << "second " << dyn_elems[1].get_center();

    std::cout << std::endl << "trying collision: " << std::endl << std::endl;

    auto first1 = Object_dynamic(BALL, p2, s, spcol);

    std::vector<Object_dynamic> dyn_elems1;
    dyn_elems1.push_back(first1);
    std::cout << "dyn elem:" << std::endl;
    print_speed(dyn_elems1[0].get_speed());
    std::cout <<  dyn_elems1[0].get_center();
    std::cout << dyn_elems1[0].get_size();

    Point wall_center = {1380, 1500, 1000};
    Size wall_size = {400, 1200, 5000};
    auto stat = Object_static(WALL, wall_center, wall_size);
    stat_elems.push_back(stat);
    std::cout << std::endl << "wall:" << std::endl << std::endl << stat_elems[0].get_size() << stat_elems[0].get_center();

    auto handler1 = Handler(dyn_elems1, stat_elems, act_elems, actr_elems, player, camera);

    handler1.update(1, camera);
    std::cout << std::endl << "one second gone:" << std::endl << std::endl;

    std::cout << "dyn ";
    print_speed(dyn_elems1[0].get_speed());
    std::cout << "dyn " << dyn_elems1[0].get_center();

    handler1.update(1,camera);
    std::cout << std::endl << "two seconds gone:" << std::endl << std::endl;

    std::cout << "dyn ";
    print_speed(dyn_elems1[0].get_speed());
    std::cout << "dyn " << dyn_elems1[0].get_center();

    std::cout << std::endl << "trying player: " << std::endl << std::endl;

    auto first2 = Object_dynamic(BALL, p2, s, spcol);

    std::vector<Object_dynamic> dyn_elems2;
    dyn_elems2.push_back(first2);
    std::cout << "dyn elem:" << std::endl;
    print_speed(dyn_elems2[0].get_speed());
    std::cout <<  dyn_elems2[0].get_center();
    std::cout << dyn_elems2[0].get_size();

    Point player_center = {1100,1300,1000};
    Size player_size = {400,400,5000};
    auto pl1 = Player(player_center, player_size);
    std::cout << std::endl << "player:" << std::endl << std::endl << pl1.get_size() << pl1.get_center();

    stat_elems.clear();

    auto handler2 = Handler(dyn_elems2, stat_elems, act_elems, actr_elems, pl1, camera);

    handler2.update(1,camera);
    std::cout << std::endl << "one second gone:" << std::endl << std::endl;

    std::cout << "dyn ";
    print_speed(dyn_elems2[0].get_speed());
    std::cout << "dyn " << dyn_elems2[0].get_center();

    handler2.update(1,camera);
    std::cout << std::endl << "two seconds gone:" << std::endl << std::endl;

    std::cout << "dyn ";
    print_speed(dyn_elems2[0].get_speed());
    std::cout << "dyn " << dyn_elems2[0].get_center();

    return 0;
}