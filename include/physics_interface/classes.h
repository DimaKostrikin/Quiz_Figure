#ifndef PHYSICS_INTERFACE_CLASSES_H
#define PHYSICS_INTERFACE_CLASSES_H

#include <iostream>
#include <vector>
#include <cmath>

#define Z_ACCELERATION 980
#define WINDAGE 20 //Достаточно ли?
#define FRICTION 100 //Достаточно ли?
#define LOSS_RATE 0.7

struct Point {
    int x;
    int y;
    int z;
    friend std::ostream& operator<< (std::ostream &out, const Point &point) {
        out << "Center: (" << point.x << ", " << point.y << ", " << point.z << ")"<< std::endl;
        return out;
    }
};

struct Speed {
    int dx; // mm/sec
    int dy;
    int dz;
    friend std::ostream& operator<< (std::ostream &out, const Speed &speed) {
        out << "Speed: (" << speed.dx << ", " << speed.dy << ", " << speed.dz << ")"<< std::endl;
        return out;
    }
};

struct Size {
    int height; //mm
    int length;
    int width;
    friend std::ostream& operator<< (std::ostream &out, const Size &size) {
        out << "Size: (" << size.height << ", " << size.length << ", " << size.width << ")"<< std::endl;
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

class Object {
public:
    Object(int e_type);
    Object(int e_type, Point &p);
    ~Object();

    int get_elem_type();
    Point get_center();
    void set_center(Point &p);

private:
    int elem_type;
    Point center;
};

class Object_dynamic : public Object {
public:
    Object_dynamic(int e_type, unsigned int r);
    Object_dynamic(int e_type, unsigned int r, Point &p);
    Object_dynamic(int e_type, unsigned int r, Speed &s);
    Object_dynamic(int e_type, unsigned int r, Point &p, Speed &s);
    ~Object_dynamic();

    Speed get_speed();
    void set_speed(Speed &s);
    void set_radius(unsigned int r);
    unsigned int get_radius();

private:
    Speed speed;
    unsigned int radius;
};

class Player : public Object_dynamic {
public:
    Player(int e_type, unsigned int h, unsigned int r, Point &p);
    ~Player();

    void take_elem(Object_dynamic &obj);

private:
    //В дальнейшем необходимо сделать const или же объявлять глобальную переменную
    unsigned int height;
};

class Object_static : public Object {
public:
    Object_static(int e_type, Point &p, unsigned int h, unsigned int l, unsigned int w);
    ~Object_static();

    unsigned int get_height();
    unsigned int get_length();
    unsigned int get_width();

private:
    //Можно сделать const в дальнейшем
    unsigned int height;
    unsigned int length;
    unsigned int width;
};

//Реализация Дмитрия
class Object_activated : public Object {};

class Handler {
public:
    Handler(std::vector<Object_dynamic> &d, std::vector<Object_static> &s, std::vector<Object_activated> &a, Player &p);
    ~Handler();

    void default_speed_change(Object_dynamic &dyn);
    void coll_speed_change(Object_dynamic &dyn1, Object_dynamic &dyn2);
    void coll_speed_change(Object_dynamic &dyn, Object_static &stat);
    bool collision(Object_dynamic &first, Object_dynamic &second);
    bool collision(Object_dynamic &first, Object_static &second);
    void position_change(Object_dynamic &dyn, size_t i);
    void updater();

private:
    Player player;
    std::vector<Object_dynamic> dyn_elems;
    std::vector<Object_static> stat_elems;
    std::vector<Object_activated> act_elems;
};



#endif