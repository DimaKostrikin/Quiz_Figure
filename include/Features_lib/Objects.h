#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>

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
    int dx;
    int dy;
    int dz;
    friend std::ostream& operator<< (std::ostream &out, const Speed &speed) {
        out << "Speed: (" << speed.dx << ", " << speed.dy << ", " << speed.dz << ")"<< std::endl;
        return out;
    }
};

struct Size {
    int height;
    int length;
    int width;
    friend std::ostream& operator<< (std::ostream &out, const Size &size) {
        out << "Size: (" << size.height << ", " << size.length << ", " << size.width << ")"<< std::endl;
        return out;
    }
};

enum type_elem {
    START,
    FINISH,
    CONNECT,
    SAVE,

    PLAYER,  // Игрок

    WALL,  // Статические объекты
    HINT,
    PLATFORM,
    STAIRS,

    CUBE,  // Динамические объекты
    BALL,

    DOOR,  // Активируемые объекты
    BUTTON,

    STEP,  // Активаторы
    HOLE,
    FAN,

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
    Speed speed = {0, 0, 0};
public:
    Object_dynamic(const int& elem_type, Point& c, Size& sz);
    Object_dynamic(const int& elem_type, Point& c, Size& sz, Speed& sd);
    ~Object_dynamic() = default;

    Speed get_speed() const;
    Speed& get_speed();
    void set_speed(Speed& sd);
    void update_position();
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

class Object_influence : public Object_static {
    Player& player;
public:
    Object_influence(const int& elem_type, Point& c, Size& sz, Player& pl);
    ~Object_influence() = default;
    void update_player();
};

class Object_activated : public Object_static {
    bool activated = false;
public:
    Object_activated(const int& elem_type, Point& c, Size& sz);
    ~Object_activated() = default;
    bool is_activated();
    void activate();
    void deactivate();
};

class Object_activator : public Object_activated {
    Object_activated& linked_object;
public:
    Object_activator(const int& elem_type, Point& c, Size& sz, Object_activated& linked_obj);
    ~Object_activator() = default;
    void activate_linked_object();
    void deactivate_linked_object();
    Object_activated& get_linked_object();
};

#endif //OBJECTS_H