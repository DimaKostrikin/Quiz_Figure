#include "../include/physics_interface/classes.h"

    Object::Object(){}
    Object::Object(int e_type) : elem_type(e_type) {}
    Object::Object(int e_type, Point &p) : elem_type(e_type), center(p) {}
    Object::~Object(){}

    int Object::get_elem_type(){}
    Point Object::get_center(){}
    void Object::set_center(Point &p){}


    Object_dynamic::Object_dynamic(){}
    Object_dynamic::Object_dynamic(int e_type) : Object(e_type){}
    Object_dynamic::Object_dynamic(int e_type, Point &p) : Object(e_type, p){}
    Object_dynamic::Object_dynamic(int e_type, Point &p, unsigned int r) : Object(e_type, p), radius(r){}
    Object_dynamic::Object_dynamic(int e_type, Point &p, unsigned int r, Speed &s) : Object(e_type, p), radius(r), speed(s){}
    Object_dynamic::~Object_dynamic(){}

    Speed Object_dynamic::get_speed(){}
    void Object_dynamic::set_speed(Speed &s){}
    void Object_dynamic::set_radius(unsigned int r){}
    unsigned int Object_dynamic::get_radius(){}


    Player::Player(){}
    Player::Player(int e_type, unsigned int h, unsigned int r, Point& p) : Object_dynamic(e_type, p, r), height(h){}
    Player::~Player(){}

    void Player::take_elem(Object_dynamic &obj){}


    Object_static::Object_static(){}
    Object_static::Object_static(int e_type, Point& p, unsigned int h, unsigned int l, unsigned int w) :
    Object_static::Object(e_type, p), height(h), length(l), width(w){}
    Object_static::~Object_static(){}

    unsigned int Object_static::get_height(){}
    unsigned int Object_static::get_length(){}
    unsigned int Object_static::get_width(){}


    Handler::Handler(std::vector<Object_dynamic> &d, std::vector<Object_static> &s, std::vector<Object_activated> &a, Player &p) :
    player(p), dyn_elems(d), stat_elems(s), act_elems(a){}
    Handler::~Handler(){}

    void Handler::speed_change(Object_dynamic &dyn){}
    void Handler::collision(Object &first, Object &second){}
    void Handler::position_change(Object_dynamic &dyn){}
    void Handler::updater(){}
