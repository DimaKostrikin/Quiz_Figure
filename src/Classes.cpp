#include "../include/physics_interface/classes.h"

    Object::Object(int e_type) : elem_type(e_type) {
    center.x = center.y = center.z = 0;
    }
    Object::Object(int e_type, Point &p) : elem_type(e_type), center(p) {}
    Object::~Object(){}
    int Object::get_elem_type(){
    return elem_type;
    }
    Point Object::get_center(){
    return center;
    }
    void Object::set_center(Point &p){
    center = p;
    }



    Object_dynamic::Object_dynamic(int e_type, unsigned int r) : Object(e_type), radius(r){
        speed.dx = speed.dy = speed.dz = 0;
    }
    Object_dynamic::Object_dynamic(int e_type, unsigned int r, Point &p) : Object(e_type, p), radius(r){
        speed.dx = speed.dy = speed.dz = 0;
    }
    Object_dynamic::Object_dynamic(int e_type, unsigned int r, Speed &s) : Object(e_type), radius(r), speed(s){}
    Object_dynamic::Object_dynamic(int e_type, unsigned int r, Point &p, Speed &s) : Object(e_type, p), radius(r), speed(s){}
    Object_dynamic::~Object_dynamic(){}

    Speed Object_dynamic::get_speed(){
    return speed;
    }
    void Object_dynamic::set_speed(Speed &s){
    speed = s;
    }
    void Object_dynamic::set_radius(unsigned int r){
    radius = r;
    }
    unsigned int Object_dynamic::get_radius(){
    return radius;
    }


    Player::Player(int e_type, unsigned int h, unsigned int r, Point& p) : Object_dynamic(e_type, r, p), height(h){}
    Player::~Player(){}

    void Player::take_elem(Object_dynamic &obj){}//TODO


    Object_static::Object_static(int e_type, Point& p, unsigned int h, unsigned int l, unsigned int w) :
    Object_static::Object(e_type, p), height(h), length(l), width(w){}
    Object_static::~Object_static(){}

    unsigned int Object_static::get_height(){
        return height;
    }
    unsigned int Object_static::get_length(){
        return length;
    }
    unsigned int Object_static::get_width(){
        return width;
    }


    Handler::Handler(std::vector<Object_dynamic> &d, std::vector<Object_static> &s, std::vector<Object_activated> &a, Player &p) :
    player(p), dyn_elems(d), stat_elems(s), act_elems(a){}
    Handler::~Handler(){}

    void Handler::speed_change(Object_dynamic &dyn){}//TODO
    void Handler::collision(Object &first, Object &second){}//TODO
    void Handler::position_change(Object_dynamic &dyn){}
    void Handler::updater(){
        for(size_t i = 0; i < dyn_elems.size(); ++i) {
            position_change(dyn_elems[i]);
        }
    }//TODO Обход всех элементов, сравнение центров и скоростей -> коллизии + изменение скоростей
