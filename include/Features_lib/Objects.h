#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include "Graphics_lib/Model_class.h"



enum type_elem {
    SAVE, // для тулбара, сорян
    DELETE,

    PLAYER,  // Игрок

    WALL,// Статические объекты
    WALL_STATIC, // Статические объекты
    HINT,
    PLATFORM,
    STAIRS,
    START,
    FINISH,

    CUBE,  // Динамические объекты
    BALL,

    DOOR,  // Активируемые объекты
    BUTTON,

    STEP,  // Активаторы
    HOLE,
    FAN,
    TELEPORT,

    TELEPORT_IN,
    TELEPORT_OUT,// Взаимодействие с параметрами игрока
    LASER,
    JUMPER,


    COUNT //кол-во знач в enum
};



class Object {  // Базовый класс объектов
protected:
    glm::vec3 center;
    unsigned int elem_type;
    unsigned int id;
public:
    Object(unsigned int elem_type, glm::vec3& c);
    virtual ~Object() = default;
    unsigned int get_elem_type();
    glm::vec3 get_center() const;
    glm::vec3& get_center();

    unsigned int get_id() const;
    unsigned int &get_id();


    void set_center(glm::vec3& c);
};

class Object_static : public Object {
    glm::vec3 size;
    Model our_model;
public:
    Object_static(const int& elem_type, glm::vec3& c, glm::vec3& sz);
    ~Object_static() = default;
    glm::vec3 get_size() const;
    glm::vec3& get_size();
    void set_size(glm::vec3& sz);
    Model& get_model();
    void update_model();
};

class Object_dynamic : public Object_static {
    glm::vec3 speed = {0,0,0};
    bool on_floor = false;
    bool taken = false;
public:
    Object_dynamic(const int& elem_type, glm::vec3& c, glm::vec3& sz);
    Object_dynamic(const int& elem_type, glm::vec3& c, glm::vec3& sz, bool on_floor);
    Object_dynamic(const int& elem_type, glm::vec3& c, glm::vec3& sz, glm::vec3& sd);
    Object_dynamic(const int& elem_type, glm::vec3& c, glm::vec3& sz, glm::vec3& sd, bool on_floor);
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
    Player(glm::vec3& c, glm::vec3& sz);
    ~Player() = default;
    int get_hp() const;
    int& get_hp();
    void set_status(bool st);
    bool get_status();
};


class Object_influence : public Object_static {
    Player& player;
public:
    Object_influence(const int& elem_type, glm::vec3& c, glm::vec3& sz, Player& pl);
    ~Object_influence() = default;
    void update_player();
};

class Object_activated : public Object_static {
    bool activated = false;
public:
    Object_activated(const int& elem_type, glm::vec3& c, glm::vec3& sz);
    ~Object_activated() = default;
    bool is_activated();
    void activate();
    void deactivate();
};

class Object_activator : public Object_activated {
    std::list<Object_activated>::iterator &linked_object;
public:
    Object_activator(const int& elem_type, glm::vec3& c, glm::vec3& sz, std::list<Object_activated>::iterator &linked_object);
    ~Object_activator() = default;
    void activate_linked_object();
    void deactivate_linked_object();
    std::list<Object_activated>::iterator &get_linked_object();
};

#endif //OBJECTS_H