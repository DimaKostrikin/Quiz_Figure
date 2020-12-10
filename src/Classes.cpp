#include "physics_interface/classes.h"

#define passed_time 1 // Временная затычка вместо прошедшего времени
#define SPEED_ERROR 100
#define X_COLLISION 1
#define Y_COLLISION 2
#define Z_COLLISION 3

void print_speed(glm::vec3& speed) {
    std::cout << "Speed: (" << speed.x << ", " << speed.y << ", " << speed.z << ")"<< std::endl;
    return;
}

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
    glm::vec3 new_speed = {0,0,0};
    if(!dyn.get_on_floor()) {//элемент не на поверхности
        new_speed.z = dyn.get_speed().z - Z_ACCELERATION * passed_time;
        if (sqrt(pow(dyn.get_speed().x, 2) + pow(dyn.get_speed().y, 2)) <= SPEED_ERROR) {
            new_speed.x = 0;
            new_speed.y = 0;
            dyn.set_speed(new_speed);
            return;
        }
        if(WINDAGE * passed_time > abs(dyn.get_speed().x)) {
            new_speed.x = 0;
        }
        else {
            new_speed.x = dyn.get_speed().x - WINDAGE * passed_time * dyn.get_speed().x / abs(dyn.get_speed().x);
        }
        if(WINDAGE * passed_time > abs(dyn.get_speed().y)) {
            new_speed.y = 0;
        }
        else {
            new_speed.y = dyn.get_speed().y - WINDAGE * passed_time * dyn.get_speed().y / abs(dyn.get_speed().y);
        }
        dyn.set_speed(new_speed);
        return;
    }
    if(FRICTION * passed_time > abs(dyn.get_speed().x)) {
        new_speed.x = 0;
    }
    else {
        new_speed.x = dyn.get_speed().x - FRICTION * passed_time * dyn.get_speed().x / abs(dyn.get_speed().x);
    }
    if(FRICTION * passed_time > abs(dyn.get_speed().y)) {
        new_speed.y = 0;
    }
    else {
        new_speed.y = dyn.get_speed().y - FRICTION * passed_time * dyn.get_speed().y / abs(dyn.get_speed().y);
    }
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
    glm::vec3 new_speed = {0,0,0};
    if(stat.get_elem_type() == WALL) {//стена
        if(coll_type == X_COLLISION) {
            new_speed.z = dyn.get_speed().z;
            new_speed.x = -LOSS_RATE * dyn.get_speed().x;
            new_speed.y = dyn.get_speed().y;
            dyn.set_speed(new_speed);
            return;
        }
        if(coll_type == Y_COLLISION) {
            new_speed.z = dyn.get_speed().z;
            new_speed.x = dyn.get_speed().x;
            new_speed.y = -LOSS_RATE * dyn.get_speed().y;
            dyn.set_speed(new_speed);
            return;
        }
    }
    if(stat.get_elem_type() == FLOOR) {//пол
        new_speed.z = -LOSS_RATE * dyn.get_speed().z;
        if(abs(dyn.get_speed().z) <= SPEED_ERROR) {
            new_speed.z = 0;
            dyn.set_on_floor(true);
        }
        new_speed.x = dyn.get_speed().x;
        new_speed.y = dyn.get_speed().y;
        dyn.set_speed(new_speed);
        return;
    }
}

void Handler::coll_speed_player(Object_dynamic &dyn, int coll_type) {
    glm::vec3 new_speed = {0,0,0};
    if(coll_type == X_COLLISION) {
        new_speed.z = dyn.get_speed().z;
        new_speed.x = -LOSS_RATE * dyn.get_speed().x;
        new_speed.y = dyn.get_speed().y;
        dyn.set_speed(new_speed);
        return;
    }
    if(coll_type == Y_COLLISION) {
        new_speed.z = dyn.get_speed().z;
        new_speed.x = dyn.get_speed().x;
        new_speed.y = -LOSS_RATE * dyn.get_speed().y;
        dyn.set_speed(new_speed);
        return;
    }
    if(coll_type == Z_COLLISION) {
        new_speed.z = -LOSS_RATE * dyn.get_speed().z;
        new_speed.x = dyn.get_speed().x;
        new_speed.y = dyn.get_speed().y;
        dyn.set_speed(new_speed);
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
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(dyn.get_center().x, dyn.get_size().length, player.get_center().x, player.get_size().length) &&
       cmp(dyn.get_center().y, dyn.get_size().width, player.get_center().y, player.get_size().width) &&
       cmp(dyn.get_center().z, dyn.get_size().height, player.get_center().z, player.get_size().height)) {
        unsigned int range = abs(dyn.get_center().x - player.get_center().x);
        unsigned int characteristics = player.get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(dyn.get_center().y - player.get_center().y);
        characteristics = player.get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(dyn.get_center().z - player.get_center().z);
        characteristics = player.get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision(Object_dynamic &first, Object_static &second) {
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first.get_center().x, first.get_size().length, second.get_center().x, second.get_size().length) &&
       cmp(first.get_center().y, first.get_size().width, second.get_center().y, second.get_size().width) &&
       cmp(first.get_center().z, first.get_size().height, second.get_center().z, second.get_size().height)) {
        unsigned int range = abs(first.get_center().x - second.get_center().x);
        unsigned int characteristics = second.get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(first.get_center().y - second.get_center().y);
        characteristics = second.get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(first.get_center().z - second.get_center().z);
        characteristics = second.get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

void Handler::position_change(Object_dynamic &dyn, size_t i) {
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
    Point new_center = {0,0,0};
    new_center.x = dyn.get_center().x + dyn.get_speed().x * passed_time;
    new_center.y = dyn.get_center().y + dyn.get_speed().y * passed_time;
    new_center.z = dyn.get_center().z + dyn.get_speed().z * passed_time;
    dyn.set_center(new_center);
    default_speed_change(dyn);
}

//Пока что всегда на полу
void Handler::player_update() {
    glm::vec3 new_speed = {0,0,0};
    Point old_center = player.get_center();
    Point new_center;
    new_center.x = player.get_speed().x * passed_time + player.get_center().x;
    new_center.y = player.get_speed().y * passed_time + player.get_center().y;
    new_center.z = player.get_speed().z * passed_time + player.get_center().z;
    player.set_center(new_center);
    if(1) {//Кнопка не нажата, необходимо реализовать
        player.set_speed(new_speed);
    }
    else {
        new_speed = new_speed; //Необходима реализация камеры для задания скоростей в определенных направлениях
    }
    int coll_type = 0;
    for(size_t i = 0; i < dyn_elems.size(); ++i) {
        coll_type = player_collision(dyn_elems[i]);
        if(coll_type) {
            coll_speed_player(dyn_elems[i], coll_type);
        }
    }
    for(size_t j = 0; j < stat_elems.size(); ++j) {
        coll_type = collision(player, stat_elems[j]);
        if(coll_type == X_COLLISION) {
            player.get_center().x = old_center.x;
        }
        if(coll_type == Y_COLLISION) {
            player.get_center().y = old_center.y;
        }
        if(coll_type == Z_COLLISION) {
            player.get_center().z = old_center.z;
        }
    }
}

void Handler::updater() {
    player_update();
    for(size_t i = 0; i < dyn_elems.size(); ++i) {
        position_change(dyn_elems[i], i);
    }
}