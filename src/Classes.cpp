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

    void Player::take_elem(Object_dynamic &obj){}//TODO вопрос с камерой


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

    void Handler::default_speed_change(Object_dynamic &dyn) {
        Speed new_speed;
        if() {//элемент не на поверхности(добавить новое поле?)
            new_speed.dz = dyn.get_speed().dz - Z_ACCELERATION * passed_time;
            if (sqrt(pow(dyn.get_speed().dx, 2) + pow(dyn.get_speed().dy, 2)) < 5) {
                new_speed.dx = 0;
                new_speed.dy = 0;
                dyn.set_speed(new_speed);
                return;
            }
            new_speed.dx = dyn.get_speed().dx - WINDAGE * passed_time;
            new_speed.dy = dyn.get_speed().dy - WINDAGE * passed_time;
            dyn.set_speed(new_speed);
            return;
        }
        new_speed.dx = dyn.get_speed().dx - FRICTION * passed_time;
        new_speed.dy = dyn.get_speed().dy - FRICTION * passed_time;
        new_speed.dz = 0;
        dyn.set_speed(new_speed);
        return;
    }
    void Handler::coll_speed_change(Object_dynamic &dyn1, Object_dynamic &dyn2){}//TODO *HARD Возможно поможет пакет математики буста
    void Handler::coll_speed_change(Object_dynamic &dyn, Object_static &stat){//разложение неверное, нужно учитывать скорость относительно стены
        Speed new_speed;
        if(stat.get_elem_type() == WALL){//стена
            new_speed.dz = dyn.get_speed().dz;
            new_speed.dx = -LOSS_RATE * dyn.get_speed().dx;//double to int, думаю, ничего страшного
            new_speed.dy = -LOSS_RATE * dyn.get_speed().dy;
            return;
        }
        if(stat.get_elem_type() == FLOOR) {//пол
            new_speed.dz = -LOSS_RATE * dyn.get_speed().dz;
            new_speed.dx = dyn.get_speed().dx;
            new_speed.dy = dyn.get_speed().dy;
            return;
        }

    }
    bool Handler::collision(Object_dynamic &first, Object_dynamic &second){
        unsigned int bigger = 0;
        if(first.get_radius() > second.get_radius()) {
            bigger = first.get_radius();
        }
        else {
            bigger = second.get_radius();
        }
        if(sqrt(pow(abs(first.get_center().x - second.get_center().x), 2) + pow(abs(first.get_center().y - second.get_center().y), 2)
        + pow(abs(first.get_center().z - second.get_center().z), 2)) < bigger) {
            return true;
        }
        return false;
    }//отдельная обработка для игрока
    bool Handler::collision(Object_dynamic &first, Object_static &second){
        unsigned int range = abs(first.get_center().x - second.get_center().x);
        unsigned int characteristics = abs(first.get_radius() + second.get_length()/2);//Длина всегда по x
        if(range < characteristics) {
            return true;
        }
        range = abs(first.get_center().y - second.get_center().y);
        characteristics = abs(first.get_radius() + second.get_width()/2);
        if(range < characteristics) {
            return true;
        }
        range = abs(first.get_center().z - second.get_center().z);
        characteristics = abs(first.get_radius() + second.get_height()/2);
        if(range < characteristics) {
            return true;
        }
        return false;
    }
    void Handler::position_change(Object_dynamic &dyn, size_t i){
        default_speed_change(dyn);
        for(size_t j = 0; j < dyn_elems.size(); ++j) {
            if(j == i){
                continue;
            }
            if(collision(dyn, dyn_elems[j])){
                coll_speed_change(dyn, dyn_elems[j]); //Сделать, чтобы скорость не менялась дважды!!!!
            }
        }
        for(size_t j = 0; j < stat_elems.size(); ++j) {
            if(collision(dyn, stat_elems[j])){
                coll_speed_change(dyn, stat_elems[j]);
            }
        }
        Point new_center;
        new_center.x = dyn.get_center().x + dyn.get_speed().dx * passed_time;
        new_center.y = dyn.get_center().y + dyn.get_speed().dy * passed_time;
        new_center.z = dyn.get_center().z + dyn.get_speed().dz * passed_time;
        dyn.set_center(new_center);
    }
    void Handler::updater(){
        for(size_t i = 0; i < dyn_elems.size(); ++i) {
            position_change(dyn_elems[i], i);
        }
    }