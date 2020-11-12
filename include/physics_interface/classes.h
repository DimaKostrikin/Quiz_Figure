#ifndef PHYSICS_INTERFACE_CLASSES_H
#define PHYSICS_INTERFACE_CLASSES_H

#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
    int z;
};

struct Speed {
    int dx;
    int dy;
    int dz;
};

class Object {
public:
    Object();
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
    Object_dynamic();
    Object_dynamic(int e_type);
    Object_dynamic(int e_type, Point &p);
    Object_dynamic(int e_type, Point &p, unsigned int r);
    Object_dynamic(int e_type, Point &p, unsigned int r, Speed &s);
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
    Player();
    Player(int e_type, unsigned int h, unsigned int r, Point &p);
    ~Player();

    void take_elem(Object_dynamic &obj);

private:
    //В дальнейшем необходимо сделать const или же объявлять глобальную переменную
    unsigned int height;
};

class Object_static : public Object {
public:
    Object_static();
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

    void speed_change(Object_dynamic &dyn);
    void collision(Object &first, Object &second);
    void position_change(Object_dynamic &dyn);
    void updater();

private:
    Player player;
    std::vector<Object_dynamic> dyn_elems;
    std::vector<Object_static> stat_elems;
    std::vector<Object_activated> act_elems;
};

#endif
