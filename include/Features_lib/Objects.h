#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>


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
    // для тулбара, сорян
    DELETE,

    START,
    FINISH,
    CONNECT,
    SAVE,

    PLAYER,  // Игрок

    WALL,
    WALL_STATIC, // Статические объекты
    HINT,
    PLATFORM,
    STAIRS,

    CUBE,  // Динамические объекты
    BALL,

    DOOR,  // Активируемые объекты
    BUTTON,

    STEP,
    TELEPORT_IN,
    TELEPORT_OUT,// Активаторы
    HOLE,
    FAN,

    TELEPORT,  // Взаимодействие с параметрами игрока
    LASER,
    JUMPER,

    COUNT
};



class Object {  // Базовый класс объектов
    Point center;
    unsigned int elem_type;
    unsigned int id;
public:
    Object(unsigned int elem_type, Point& c);
    virtual ~Object() = default;
    unsigned int get_elem_type();
    Point get_center() const;
    Point& get_center();

    unsigned int get_id() const;
    unsigned int &get_id();


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
    bool taken = false;
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
    bool get_taken();
    void set_taken(bool tk);
};

class Player : public Object_dynamic {
    int hp = 100;
    bool status = false;
public:
    Player(Point& c, Size& sz);
    ~Player() = default;
    int get_hp() const;
    int& get_hp();
    void set_status(bool st);
    bool get_status();
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
    std::list<Object_activated>::iterator &linked_object;
public:
    Object_activator(const int& elem_type, Point& c, Size& sz, std::list<Object_activated>::iterator &linked_object);
    ~Object_activator() = default;
    void activate_linked_object();
    void deactivate_linked_object();
    std::list<Object_activated>::iterator &get_linked_object();
};

#endif //OBJECTS_H