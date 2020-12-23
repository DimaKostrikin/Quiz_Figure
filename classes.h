#ifndef PHYSICS_INTERFACE_CLASSES_H
#define PHYSICS_INTERFACE_CLASSES_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>

#include "glm/glm/glm/glm.hpp"
#include "glm/glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/glm/gtc/type_ptr.hpp"
#include "glm/glm/glm/gtx/vector_angle.hpp"

#define Z_ACCELERATION 980
#define WINDAGE 20 //Достаточно ли?
#define FRICTION 100 //Достаточно ли?
#define LOSS_RATE 0.7
#define PLAYER_SPEED 1000
#define PLAYER_RANGE 2000
#define RANGE_DROP 1000

void print_speed(glm::vec3& speed);

struct Point {
    int x;
    int y;
    int z;
    friend std::ostream& operator<< (std::ostream &out, const Point &point) {
        out << "Center: (" << point.x << ", " << point.y << ", " << point.z << ")"<< std::endl;
        return out;
    }
};

struct Size {
    int length;
    int width;
    int height; //mm
    friend std::ostream& operator<< (std::ostream &out, const Size &size) {
        out << "Size: (" << size.length << ", " << size.width  << ", " <<  size.height << ")"<< std::endl;
        return out;
    }
};

enum type_elem {
    PLAYER,  // Игрок

    WALL,  // Статические объекты
    FLOOR,
    HINT,
    PLATFORM,
    STAIRS,

    CUBE,  // Динамические объекты
    BALL,

    DOOR,  // Активируемые объекты
    BUTTON,

    STEP,  // Активаторы
    HOLE,

    TELEPORT,  // Взаимодействие с параметрами игрока
    LASER,
    JUMPER
};

class Object {  // Базовый класс объектов
    Point center;
    unsigned int elem_type;
public:
    Object(unsigned int elem_type, Point& c);
    virtual ~Object() = default;
    unsigned int get_elem_type();
    Point get_center() const;
    Point& get_center();

    void set_center(Point& c);
};

class Object_static : public Object {
    Size size;
public:
    Object_static(const int& elem_type, Point& c, Size& sz);
    ~Object_static() = default;
    Size get_size() const;
    Size& get_size();
    void set_size(Size& sz);
};

class Object_dynamic : public Object_static {
    glm::vec3 speed = {0,0,0};
    bool on_floor = false;
public:
    Object_dynamic(const int& elem_type, Point& c, Size& sz);
    Object_dynamic(const int& elem_type, Point& c, Size& sz, bool on_floor);
    Object_dynamic(const int& elem_type, Point& c, Size& sz, glm::vec3& sd);
    Object_dynamic(const int& elem_type, Point& c, Size& sz, glm::vec3& sd, bool on_floor);
    ~Object_dynamic() = default;

    glm::vec3 get_speed() const;
    glm::vec3& get_speed();
    void set_speed(glm::vec3& sd);
    bool get_on_floor();
    void set_on_floor(bool on);
};

class Player : public Object_dynamic {
    int hp = 100;
    bool status = false;
    std::list<Object_dynamic>::iterator object;
public:
    Player(Point& c, Size& sz);
    ~Player() = default;
    std::list<Object_dynamic>::iterator& drop_object();
    void take_object(std::list<Object_dynamic>::iterator &object_taken);
    int get_hp() const;
    int& get_hp();
    void set_status(bool st);
    bool get_status();
};

//Реализация Дмитрия
class Object_activated : public Object_static {};

class Object_activator : public Object_static {};

class Handler {
public:
    Handler(std::list<Object_dynamic> &d, std::list<Object_static> &s, std::list<Object_activated> &a,
            std::list<Object_activator> &ar, Player &p, glm::vec3& cam);
    ~Handler() = default;
    void update(float ps_time, glm::vec3& cam);

private:
    void default_speed_change(std::list<Object_dynamic>::iterator &dyn);
    void coll_speed_change_dyn(std::list<Object_dynamic>::iterator &dyn1, std::list<Object_dynamic>::iterator &dyn2);
    void coll_speed_player(std::list<Object_dynamic>::iterator &dyn, int coll_type);
    void coll_speed_change(std::list<Object_dynamic>::iterator &dyn, int coll_type);
    bool collision_dyn(std::list<Object_dynamic>::iterator &first, std::list<Object_dynamic>::iterator &second);
    int player_collision(std::list<Object_dynamic>::iterator &dyn);
    int collision(std::list<Object_dynamic>::iterator &first, std::list<Object_static>::iterator &second);
    int collision_act(std::list<Object_dynamic>::iterator &first, std::list<Object_activated>::iterator &second);
    int collision_actr(std::list<Object_dynamic>::iterator &first, std::list<Object_activator>::iterator &second);
    void position_change(std::list<Object_dynamic>::iterator &dyn);
    bool look_at(std::list<Object_dynamic>::iterator &dyn);
    void player_speed_change();
    void player_update();

    Player player;
    std::list<Object_dynamic>& dyn_elems;
    std::list<Object_static>& stat_elems;
    std::list<Object_activated>& act_elems;
    std::list<Object_activator>& actr_elems;
    float passed_time;
    glm::vec3& camera;
};


#endif