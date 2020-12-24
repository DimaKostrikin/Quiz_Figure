#ifndef PHYSICS_INTERFACE_CLASSES_H
#define PHYSICS_INTERFACE_CLASSES_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include "Features_lib/Objects.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define Z_ACCELERATION 0.98
#define WINDAGE 20
#define FRICTION 100
#define LOSS_RATE 0.7
#define PLAYER_SPEED 2
#define PLAYER_RANGE 2000

void print_speed(glm::vec3& speed);



class Handler_physics {
public:
    Handler_physics(std::list<Object_dynamic> &d, std::list<Object_static> &s, std::list<Object_activated> &a,
            std::list<Object_activator> &ar, Player &p, glm::vec3& cam, GLFWwindow *window);
    ~Handler_physics() = default;
    void update(double ps_time);
    glm::vec3 camera;
private:
    void take_object(std::list<Object_dynamic>::iterator &object_taken);
    void drop_object(std::list<Object_dynamic>::iterator &object_dropped);
    void default_speed_change(std::list<Object_dynamic>::iterator &dyn);
    void coll_speed_change_dyn(std::list<Object_dynamic>::iterator &dyn1, std::list<Object_dynamic>::iterator &dyn2);
    void coll_speed_player(std::list<Object_dynamic>::iterator &dyn, int coll_type);
    void coll_speed_change(std::list<Object_dynamic>::iterator &dyn, int coll_type);
    bool collision_dyn(std::list<Object_dynamic>::iterator &first, std::list<Object_dynamic>::iterator &second);
    int player_collision(std::list<Object_dynamic>::iterator &dyn);
    int collision(std::list<Object_dynamic>::iterator &first, std::list<Object_static>::iterator &second);
    int collision_player(std::list<Object_static>::iterator &second);
    int collision_act(std::list<Object_dynamic>::iterator &first, std::list<Object_activated>::iterator &second);
    int collision_act_player(std::list<Object_activated>::iterator &second);
    int collision_actr(std::list<Object_dynamic>::iterator &first, std::list<Object_activator>::iterator &second);
    int collision_actr_player(std::list<Object_activator>::iterator &second);
    void position_change(std::list<Object_dynamic>::iterator &dyn);
    bool look_at(std::list<Object_dynamic>::iterator &dyn);
    void player_speed_change();
    void player_update();

    Player& player;
    std::list<Object_dynamic>& dyn_elems;
    std::list<Object_static>& stat_elems;
    std::list<Object_activated>& act_elems;
    std::list<Object_activator>& actr_elems;
    double passed_time;

    GLFWwindow *window;
};


#endif
