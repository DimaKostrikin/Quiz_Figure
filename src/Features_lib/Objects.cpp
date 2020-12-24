#include "Features_lib/Objects.h"
#define ELAPSED_TIME 1 // Временная затычка вместо прошедшего времени

// Тупа объект


void print_speed(glm::vec3& speed) {
    std::cout << "Speed: (" << speed.x << ", " << speed.y << ", " << speed.z << ")"<< std::endl;
    return;
}

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

unsigned int Object::get_id() const {
    return id;
}

unsigned int &Object::get_id() {
    return id;
}

// Статические объекты

Object_static::Object_static(const int& elem_type, Point &c, Size &sz)
        : Object(elem_type, c), size(sz) {
    our_model.set_xpos(float(c.x) / 1000);
    our_model.set_ypos(float(c.z) / 1000);
    our_model.set_zpos(float(c.y) / 1000);

    our_model.set_xscale(float(size.length) / 1000);
    our_model.set_yscale(float(size.height) / 1000);
    our_model.set_zscale(float(size.width) / 1000);

}

Size Object_static::get_size() const {
    return size;
}

Size& Object_static::get_size() {
    return size;
}

void Object_static::set_size(Size &sz) {
    size = sz;
}

Model &Object_static::get_model() {
    return our_model;
}

void Object_static::update_model() {
    our_model.set_xpos(float(center.x) / 1000);
    our_model.set_ypos(float(center.z) / 1000);
    our_model.set_zpos(float(center.y) / 1000);
}



// Динамические объекты

Object_dynamic::Object_dynamic(const int& elem_type, Point& c, Size &sz)
        : Object_static(elem_type, c, sz) {}

Object_dynamic::Object_dynamic(const int& elem_type, Point& c, Size &sz, bool on)
        : Object_static(elem_type, c, sz), on_floor(on) {}

Object_dynamic::Object_dynamic(const int &elem_type, Point &c, Size &sz, glm::vec3 &sd)
        : Object_static(elem_type, c, sz), speed(sd) {}

Object_dynamic::Object_dynamic(const int &elem_type, Point &c, Size &sz, glm::vec3 &sd, bool on)
        : Object_static(elem_type, c, sz), speed(sd), on_floor(on) {}

glm::vec3 Object_dynamic::get_speed() const {
    return speed;
}

glm::vec3 &Object_dynamic::get_speed() {
    return speed;
}

void Object_dynamic::set_speed(glm::vec3 &sd) {
    speed = sd;
}

bool Object_dynamic::get_on_floor() {
    return on_floor;
}

void Object_dynamic::set_on_floor(bool on) {
    on_floor = on;
}

bool Object_dynamic::get_taken() {
    return taken;
}

void Object_dynamic::set_taken(bool tk) {
    taken = tk;
}


// Игрок

Player::Player(Point &c, Size &sz) : Object_dynamic(PLAYER, c, sz, true) {}

int Player::get_hp() const {
    return hp;
}

int& Player::get_hp() {
    return hp;
}

void Player::set_status(bool st) {
    status = st;
}

bool Player::get_status() {
    return status;
};

// Игрок



// Взаимодействие с характеристиками игрока

Object_influence::Object_influence(const int &elem_type, Point &c, Size &sz, Player& pl)
        : Object_static(elem_type, c, sz), player(pl) {}

void Object_influence::update_player() {
    if (get_elem_type() == LASER) {
        player.get_hp() -= 50;
    }
    if (get_elem_type() == JUMPER) {
        player.get_speed().z += 100;// Временная затычка. Для jumper наверное еще надо сделать направление,
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
                                   std::list<Object_activated>::iterator &linked_object)
        : Object_activated(elem_type, c, sz), linked_object(linked_object)
 {}

void Object_activator::activate_linked_object() {
    linked_object->activate();
}

void Object_activator::deactivate_linked_object() {
    linked_object->deactivate();
}

std::list<Object_activated>::iterator &Object_activator::get_linked_object() {
    return linked_object;
}
