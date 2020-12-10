#ifndef PHYSICS_INTERFACE_CLASSES_H
#define PHYSICS_INTERFACE_CLASSES_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../glm/glm/glm/glm.hpp"
#include "../glm/glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/glm/gtc/type_ptr.hpp"

#define Z_ACCELERATION 980
#define WINDAGE 20 //Достаточно ли?
#define FRICTION 100 //Достаточно ли?
#define LOSS_RATE 0.7

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

/*struct Speed {
    int dx; // mm/sec
    int dy;
    int dz;
    friend std::ostream& operator<< (std::ostream &out, const Speed &speed) {
        out << "Speed: (" << speed.dx << ", " << speed.dy << ", " << speed.dz << ")"<< std::endl;
        return out;
    }
};*/

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
public:
    Player(Point& c, Size& sz);
    ~Player() = default;
    void take_object(Object_dynamic &taked_object);
    int get_hp() const;
    int& get_hp();
};

//Реализация Дмитрия
class Object_activated : public Object {};

class Handler {
public:
    Handler(std::vector<Object_dynamic> &d, std::vector<Object_static> &s, std::vector<Object_activated> &a, Player &p);
    ~Handler() = default;
    void updater();

private:
    void default_speed_change(Object_dynamic &dyn);
    void coll_speed_change(Object_dynamic &dyn1, Object_dynamic &dyn2);
    void coll_speed_player(Object_dynamic &dyn, int coll_type);
    void coll_speed_change(Object_dynamic &dyn, Object_static &stat, int coll_type);
    bool collision(Object_dynamic &first, Object_dynamic &second);
    int player_collision(Object_dynamic &dyn);
    int collision(Object_dynamic &first, Object_static &second);
    void position_change(Object_dynamic &dyn, size_t i);
    void player_update();

    Player player;
    std::vector<Object_dynamic>& dyn_elems;
    std::vector<Object_static>& stat_elems;
    std::vector<Object_activated>& act_elems;
};


#endif