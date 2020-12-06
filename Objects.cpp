#include "Objects.h"
#define ELAPSED_TIME 2 // Временная затычка вместо прошедшего времени

// Тупа объект

Object::Object(unsigned int elem_type, Point &c) : elem_type(elem_type), center(c) {}

unsigned int Object::get_elem_type() {
    return elem_type;
}

Point Object::get_center() const {
    return center;
}

Point &Object::get_center() {
    return center;
}

void Object::set_center(Point &c) {
    center = c;
}

// Статические объекты

Object_static::Object_static(const int& elem_type, Point &c, Size &sz)
                             : Object(elem_type, c), size(sz) {}

Size Object_static::get_size() {
    return size;
}

void Object_static::set_size(Size &sz) {
    size = sz;
}

// Динамические объекты

Object_dynamic::Object_dynamic(const int& elem_type, Point& c, Size &sz)
                                : Object_static(elem_type, c, sz) {}

Object_dynamic::Object_dynamic(const int &elem_type, Point &c, Size &sz, Speed &sd)
                               : Object_static(elem_type, c, sz), speed(sd) {}

Speed Object_dynamic::get_speed() const {
    return speed;
}

Speed &Object_dynamic::get_speed() {
    return speed;
}

void Object_dynamic::set_speed(Speed &sd) {
    speed = sd;
}

void Object_dynamic::update_position() {
    auto& c = get_center();
    auto& s = get_speed();
    c.x += s.dx * ELAPSED_TIME;
    c.y += s.dy * ELAPSED_TIME;
    c.z += s.dz * ELAPSED_TIME;
}

// Игрок

Player::Player(Point &c, Size &sz) : Object_dynamic(PLAYER, c, sz) {}

int Player::get_hp() const {
    return hp;
}

int& Player::get_hp() {
    return hp;
}

// Взаимодействие с характеристиками игрока

Object_influence::Object_influence(const int &elem_type, Point &c, Size &sz, Player& pl)
                                   : Object_static(elem_type, c, sz), player(pl) {}

void Object_influence::update_player() {
    if (get_elem_type() == LASER) {
        player.get_hp() -= 50;
    }
    if (get_elem_type() == JUMPER) {
        player.get_speed().dz += 100;
        player.get_speed().dy += 100;  // Временная затычка. Для jumper наверное еще надо сделать направление,
                                       // куда он будет кидать игрока
    }
}


// Ну короче

Object_activated::Object_activated(const int &elem_type, Point &c, Size &sz)
                                   : Object_static(elem_type, c, sz) {}

bool Object_activated::is_activated() {
    return activated;
}

void Object_activated::activate() {
    activated = true;
}

void Object_activated::deactivate() {
    activated = false;
}

Object_activator::Object_activator(const int &elem_type,
                                   Point &c,
                                   Size &sz,
                                   Object_activated& linked_obj)
                                   : Object_activated(elem_type, c, sz),
                                   linked_object(linked_obj) {}

void Object_activator::activate_linked_object() {
    linked_object.activate();
}

void Object_activator::deactivate_linked_object() {
    linked_object.deactivate();
}
