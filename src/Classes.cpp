#include "../include/physics_interface/classes.h"

#define passed_time 1 // Временная затычка вместо прошедшего времени
#define SPEED_ERROR 100
#define X_COLLISION 1
#define Y_COLLISION 2
#define Z_COLLISION 3
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

Size Object_static::get_size() const {
    return size;
}

Size& Object_static::get_size() {
    return size;
}

void Object_static::set_size(Size &sz) {
    size = sz;
}

// Динамические объекты

Object_dynamic::Object_dynamic(const int& elem_type, Point& c, Size &sz)
        : Object_static(elem_type, c, sz) {}

Object_dynamic::Object_dynamic(const int& elem_type, Point& c, Size &sz, bool on)
        : Object_static(elem_type, c, sz), on_floor(on) {}

Object_dynamic::Object_dynamic(const int &elem_type, Point &c, Size &sz, Speed &sd)
        : Object_static(elem_type, c, sz), speed(sd) {}

Object_dynamic::Object_dynamic(const int &elem_type, Point &c, Size &sz, Speed &sd, bool on)
        : Object_static(elem_type, c, sz), speed(sd), on_floor(on) {}

Speed Object_dynamic::get_speed() const {
    return speed;
}

Speed &Object_dynamic::get_speed() {
    return speed;
}

void Object_dynamic::set_speed(Speed &sd) {
    speed = sd;
}

bool Object_dynamic::get_on_floor() {
    return on_floor;
}

void Object_dynamic::set_on_floor(bool on) {
    on_floor = on;
}

// Игрок

Player::Player(Point &c, Size &sz) : Object_dynamic(PLAYER, c, sz, true) {}

void Player::take_object(Object_dynamic &taked_object) {
    //Необходима реализация камеры!
    return;
}

int Player::get_hp() const {
    return hp;
}

int& Player::get_hp() {
    return hp;
}

//Обработчик

//Попробовать реализовать с учетом особенности get'ов Димы
//Рассматриваются идеальные кубы и шары, для них рассматривается радиус как основная хар-ка. Дальнейшая "фича" - связать
//с кубом углы поворота граней для более детальной обработки коллизий
Handler::Handler(std::vector<Object_dynamic> &d, std::vector<Object_static> &s, std::vector<Object_activated> &a, Player &p) :
   player(p), dyn_elems(d), stat_elems(s), act_elems(a) {}

void Handler::default_speed_change(Object_dynamic &dyn) {
    Speed new_speed = {0,0,0};
    if(!dyn.get_on_floor()) {//элемент не на поверхности
        new_speed.dz = dyn.get_speed().dz - Z_ACCELERATION * passed_time;
        if (sqrt(pow(dyn.get_speed().dx, 2) + pow(dyn.get_speed().dy, 2)) <= SPEED_ERROR) {
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
    dyn.set_speed(new_speed);
}

//Как удар в стену
void Handler::coll_speed_change(Object_dynamic &dyn1, Object_dynamic &dyn2) {
    //IDEA: Разложить скорость по новому базису(направление расстояния между центрами, 2 перпендикуляра к нему,
    //перпендикулярные между собой). Далее расчет такой же, как для стены.
    //Такая реализация позволит рассчитывать соударения, как двух движущихся объектов, так и удар о произвольно
    //расположенную стену. Необходимо глубже разобраться в glm
}//TODO *HARD Возможно поможет пакет математики буста

void Handler::coll_speed_change(Object_dynamic &dyn, Object_static &stat, int coll_type) {
    Speed new_speed = {0,0,0};
    if(stat.get_elem_type() == WALL) {//стена
        if(coll_type == X_COLLISION) {
            new_speed.dz = dyn.get_speed().dz;
            new_speed.dx = -LOSS_RATE * dyn.get_speed().dx;
            new_speed.dy = dyn.get_speed().dy;
            return;
        }
        if(coll_type == Y_COLLISION) {
            new_speed.dz = dyn.get_speed().dz;
            new_speed.dx = dyn.get_speed().dx;
            new_speed.dy = -LOSS_RATE * dyn.get_speed().dy;
            return;
        }
    }
    if(stat.get_elem_type() == FLOOR) {//пол
        new_speed.dz = -LOSS_RATE * dyn.get_speed().dz;
        if(abs(dyn.get_speed().dz) <= SPEED_ERROR) {
            new_speed.dz = 0;
            dyn.set_on_floor(true);
        }
        new_speed.dx = dyn.get_speed().dx;
        new_speed.dy = dyn.get_speed().dy;
        return;
    }
 }

void Handler::coll_speed_player(Object_dynamic &dyn, int coll_type) {
    Speed new_speed = {0,0,0};
    if(coll_type == X_COLLISION) {
        new_speed.dz = dyn.get_speed().dz;
        new_speed.dx = -LOSS_RATE * dyn.get_speed().dx;
        new_speed.dy = dyn.get_speed().dy;
        return;
    }
    if(coll_type == Y_COLLISION) {
        new_speed.dz = dyn.get_speed().dz;
        new_speed.dx = dyn.get_speed().dx;
        new_speed.dy = -LOSS_RATE * dyn.get_speed().dy;
        return;
    }
    if(coll_type == Z_COLLISION) {
        new_speed.dz = -LOSS_RATE * dyn.get_speed().dz;
        new_speed.dx = dyn.get_speed().dx;
        new_speed.dy = dyn.get_speed().dy;
        return;
    }
}

bool Handler::collision(Object_dynamic &first, Object_dynamic &second) {
    unsigned int range = first.get_size().height + second.get_size().height;
    if(sqrt(pow(first.get_center().x - second.get_center().x, 2) + pow(first.get_center().y - second.get_center().y, 2)
    + pow(first.get_center().z - second.get_center().z, 2)) < range) {
        return true;
    }
    return false;
}

int Handler::player_collision(Object_dynamic &dyn) {
    unsigned int range = abs(dyn_elems[0].get_center().x - dyn.get_center().x);
    unsigned int characteristics = abs((dyn_elems[0].get_size().length + dyn.get_size().length)/2);//Длина всегда по x
    if(range < characteristics) {
        return X_COLLISION;
    }
    range = abs(dyn_elems[0].get_center().y - dyn.get_center().y);
    characteristics = abs((dyn_elems[0].get_size().width + dyn.get_size().width)/2);//Ширина всегда по y
    if(range < characteristics) {
        return Y_COLLISION;
    }
    range = abs(dyn_elems[0].get_center().z - dyn.get_center().z);
    characteristics = abs((dyn_elems[0].get_size().height + dyn.get_size().height)/2);//Высота всегда по z
    if(range < characteristics) {
        return Z_COLLISION;
    }
    return false;
}

int Handler::collision(Object_dynamic &first, Object_static &second) {
    unsigned int range = abs(first.get_center().x - second.get_center().x);
    unsigned int characteristics = abs((first.get_size().length + second.get_size().length)/2);//Длина всегда по x
    if(range < characteristics) {
        return X_COLLISION;
    }
    range = abs(first.get_center().y - second.get_center().y);
    characteristics = abs((first.get_size().width + second.get_size().width)/2);//Ширина всегда по y
    if(range < characteristics) {
        return Y_COLLISION;
    }
    range = abs(first.get_center().z - second.get_center().z);
    characteristics = abs((first.get_size().height + second.get_size().height)/2);//Высота всегда по z
    if(range < characteristics) {
        return Z_COLLISION;
    }
    return false;
}

void Handler::position_change(Object_dynamic &dyn, size_t i) {
    default_speed_change(dyn);
    int col_type = 0;
    for(size_t j = i + 1; j < dyn_elems.size(); ++j) {
        if(collision(dyn, dyn_elems[j])) {
            coll_speed_change(dyn, dyn_elems[j]);
        }
    }
    for(size_t k = 0; k < stat_elems.size(); ++k) {
        col_type = collision(dyn, stat_elems[k]);
        if(col_type) {
            coll_speed_change(dyn, stat_elems[k], col_type);
        }
    }
    Point new_center;
    new_center.x = dyn.get_center().x + dyn.get_speed().dx * passed_time;
    new_center.y = dyn.get_center().y + dyn.get_speed().dy * passed_time;
    new_center.z = dyn.get_center().z + dyn.get_speed().dz * passed_time;
    dyn.set_center(new_center);
}

//Пока что всегда на полу
void Handler::player_update() {
    Speed new_speed = {0,0,0};
    Point old_center = dyn_elems[0].get_center();
    Point new_center;
    new_center.x = dyn_elems[0].get_speed().dx * passed_time + dyn_elems[0].get_center().x;
    new_center.y = dyn_elems[0].get_speed().dy * passed_time + dyn_elems[0].get_center().y;
    new_center.z = dyn_elems[0].get_speed().dz * passed_time + dyn_elems[0].get_center().z;
    dyn_elems[0].set_center(new_center);
    if(1) {//Кнопка не нажата, необходимо реализовать
        dyn_elems[0].set_speed(new_speed);
    }
    else {
        new_speed = new_speed; //Необходима реализация камеры для задания скоростей в определенных направлениях
    }
    int coll_type = 0;
    for(size_t i = 1; i < dyn_elems.size(); ++i) {
        coll_type = player_collision(dyn_elems[i]);
        if(coll_type) {
            coll_speed_player(dyn_elems[i], coll_type);
        }
    }
    for(size_t j = 0; j < stat_elems.size(); ++j) {
        coll_type = collision(dyn_elems[0], stat_elems[j]);
        if(coll_type == X_COLLISION) {
            dyn_elems[0].get_center().x = old_center.x;
        }
        if(coll_type == Y_COLLISION) {
            dyn_elems[0].get_center().y = old_center.y;
        }
        if(coll_type == Z_COLLISION) {
            dyn_elems[0].get_center().z = old_center.z;
        }
    }
}

//Игрок всегда 0ой в векторе элементов
void Handler::updater() {
    player_update();
    for(size_t i = 1; i < dyn_elems.size(); ++i) {
            position_change(dyn_elems[i], i);
        }
    }