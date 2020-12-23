#include "physics_interface/classes.h"

//#define passed_time 1 // Временная затычка вместо прошедшего времени
#define SPEED_ERROR 100
#define X_COLLISION 1
#define Y_COLLISION 2
#define Z_COLLISION 3

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

std::list<Object_dynamic>::iterator& Player::drop_object() {
    set_status(false);
    return object;
}

void Player::take_object(std::list<Object_dynamic>::iterator &object_taken) {
    //delete object из списка
    set_status(true);
    object_taken->set_on_floor(false);
    object = object_taken;
}

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

//Обработчик

Handler::Handler(std::list<Object_dynamic> &d, std::list<Object_static> &s, std::list<Object_activated> &a,
                 std::list<Object_activator> &ar, Player &p, glm::vec3& cam) :
        player(p), dyn_elems(d), stat_elems(s), act_elems(a), actr_elems(ar), camera(cam), passed_time(0) {}

void Handler::default_speed_change(std::list<Object_dynamic>::iterator &dyn) {
    glm::vec3 new_speed = {0,0,0};
    if(!dyn->get_on_floor()) {//элемент не на поверхности
        new_speed.z = dyn->get_speed().z - Z_ACCELERATION * passed_time;
        if (sqrt(pow(dyn->get_speed().x, 2) + pow(dyn->get_speed().y, 2)) <= SPEED_ERROR) {
            new_speed.x = 0;
            new_speed.y = 0;
            dyn->set_speed(new_speed);
            return;
        }
        if(WINDAGE * passed_time > abs(dyn->get_speed().x)) {
            new_speed.x = 0;
        }
        else {
            new_speed.x = dyn->get_speed().x - WINDAGE * passed_time * dyn->get_speed().x / abs(dyn->get_speed().x);
        }
        if(WINDAGE * passed_time > abs(dyn->get_speed().y)) {
            new_speed.y = 0;
        }
        else {
            new_speed.y = dyn->get_speed().y - WINDAGE * passed_time * dyn->get_speed().y / abs(dyn->get_speed().y);
        }
        dyn->set_speed(new_speed);
        return;
    }
    if(FRICTION * passed_time > abs(dyn->get_speed().x)) {
        new_speed.x = 0;
    }
    else {
        new_speed.x = dyn->get_speed().x - FRICTION * passed_time * dyn->get_speed().x / abs(dyn->get_speed().x);
    }
    if(FRICTION * passed_time > abs(dyn->get_speed().y)) {
        new_speed.y = 0;
    }
    else {
        new_speed.y = dyn->get_speed().y - FRICTION * passed_time * dyn->get_speed().y / abs(dyn->get_speed().y);
    }
    dyn->set_speed(new_speed);
}


void Handler::coll_speed_change_dyn(std::list<Object_dynamic>::iterator &dyn1, std::list<Object_dynamic>::iterator &dyn2) {
    glm::vec2 xy1 = {dyn1->get_speed().x, dyn1->get_speed().y};
    glm::vec2 norm_xy1 = glm::normalize(xy1);
    glm::vec2 xy2 = {dyn2->get_speed().x, dyn2->get_speed().y};
    glm::vec2 norm_xy2 = glm::normalize(xy2);
    glm::vec2 xy_dist_1 = {dyn2->get_center().x - dyn1->get_center().x, dyn2->get_center().y - dyn1->get_center().x};
    glm::vec2 norm_xy_dist_1 = glm::normalize(xy_dist_1);
    glm::vec2 xy_dist_2 = -xy_dist_1;
    glm::vec2 norm_xy_dist_2 = glm::normalize(xy_dist_2);
    float alpha1 = glm::angle(norm_xy1, norm_xy_dist_1);
    if((xy1.x == 0 && xy1.y == 0) || (xy_dist_1.x == 0 && xy_dist_1.y == 0)){
        alpha1 = 0;
    }
    float alpha2 = glm::angle(norm_xy2, norm_xy_dist_2);
    if((xy2.x == 0 && xy2.y == 0) || (xy_dist_2.x == 0 && xy_dist_2.y == 0)){
        alpha2 = 0;
    }

    glm::vec2 yz1 = {dyn1->get_speed().y, dyn1->get_speed().z};
    glm::vec2 norm_yz1 = glm::normalize(yz1);
    glm::vec2 yz2 = {dyn2->get_speed().y, dyn2->get_speed().z};
    glm::vec2 norm_yz2 = glm::normalize(yz1);
    glm::vec2 yz_dist_1 = {dyn2->get_center().y - dyn1->get_center().y, dyn2->get_center().z - dyn1->get_center().z};
    glm::vec2 norm_yz_dist_1 = glm::normalize(yz_dist_1);
    glm::vec2 yz_dist_2 = -yz_dist_1;
    glm::vec2 norm_yz_dist_2 = glm::normalize(yz_dist_2);
    float beta1 = glm::angle(norm_yz1, norm_yz_dist_1);
    if((yz1.x == 0 && yz1.y == 0) || (yz_dist_1.x == 0 && yz_dist_1.y == 0)){
        beta1 = 0;
    }
    float beta2 = glm::angle(norm_yz2, norm_yz_dist_2);
    if((yz2.x == 0 && yz2.y == 0) || (yz_dist_2.x == 0 && yz_dist_2.y == 0)){
        beta2 = 0;
    }

    glm::vec3 normal_speed_1_z = glm::rotateZ(dyn1->get_speed() * glm::cos(alpha1) * glm::cos(beta1), alpha1);
    glm::vec3 normal_speed_1 = glm::rotateX(normal_speed_1_z, beta1);
    glm::vec3 remainder_vec_1 = dyn1->get_speed() - normal_speed_1;
    glm::vec3 normal_speed_2_z = glm::rotateZ(dyn2->get_speed() * glm::cos(alpha2) * glm::cos(beta2), alpha2);
    glm::vec3 normal_speed_2 = glm::rotateX(normal_speed_2_z, beta2);
    glm::vec3 remainder_vec_2 = dyn2->get_speed() - normal_speed_2;

    glm::vec3 new_normal_1 = {normal_speed_1.x * LOSS_RATE / 2,normal_speed_1.y * LOSS_RATE / 2,
                              normal_speed_1.z * LOSS_RATE / 2};
    glm::vec3 new_normal_2 = {normal_speed_2.x * LOSS_RATE / 2,normal_speed_2.y * LOSS_RATE / 2,
                              normal_speed_2.z * LOSS_RATE / 2};

    glm::vec3 new_speed_1 = remainder_vec_1 + new_normal_1 - new_normal_2;
    glm::vec3 new_speed_2 = remainder_vec_2 + new_normal_2 - new_normal_1;
    dyn1->set_speed(new_speed_1);
    dyn2->set_speed(new_speed_2);
}

void Handler::coll_speed_change(std::list<Object_dynamic>::iterator &dyn, int coll_type) {
    glm::vec3 new_speed = {0,0,0};
    if(coll_type == X_COLLISION) {
        new_speed.z = dyn->get_speed().z;
        new_speed.x = -LOSS_RATE * dyn->get_speed().x;
        new_speed.y = dyn->get_speed().y;
        dyn->set_speed(new_speed);
        return;
    }
    if(coll_type == Y_COLLISION) {
        new_speed.z = dyn->get_speed().z;
        new_speed.x = dyn->get_speed().x;
        new_speed.y = -LOSS_RATE * dyn->get_speed().y;
        dyn->set_speed(new_speed);
        return;
    }
    if(coll_type == Z_COLLISION) {
        new_speed.z = -LOSS_RATE * dyn->get_speed().z;
        if(abs(dyn->get_speed().z) <= SPEED_ERROR) {
            new_speed.z = 0;
            dyn->set_on_floor(true);
        }
        new_speed.x = dyn->get_speed().x;
        new_speed.y = dyn->get_speed().y;
        dyn->set_speed(new_speed);
        return;
    }
}

void Handler::coll_speed_player(std::list<Object_dynamic>::iterator &dyn, int coll_type) {
    glm::vec3 new_speed = {0,0,0};
    if(coll_type == X_COLLISION) {
        new_speed.z = dyn->get_speed().z;
        new_speed.x = -LOSS_RATE * dyn->get_speed().x;
        new_speed.y = dyn->get_speed().y;
        dyn->set_speed(new_speed);
        return;
    }
    if(coll_type == Y_COLLISION) {
        new_speed.z = dyn->get_speed().z;
        new_speed.x = dyn->get_speed().x;
        new_speed.y = -LOSS_RATE * dyn->get_speed().y;
        dyn->set_speed(new_speed);
        return;
    }
    if(coll_type == Z_COLLISION) {
        new_speed.z = -LOSS_RATE * dyn->get_speed().z;
        new_speed.x = dyn->get_speed().x;
        new_speed.y = dyn->get_speed().y;
        dyn->set_speed(new_speed);
        return;
    }
}

bool Handler::collision_dyn(std::list<Object_dynamic>::iterator &first, std::list<Object_dynamic>::iterator &second) {
    unsigned int range = first->get_size().height + second->get_size().height;
    if(sqrt(pow(first->get_center().x - second->get_center().x, 2) + pow(first->get_center().y - second->get_center().y, 2)
            + pow(first->get_center().z - second->get_center().z, 2)) < range) {
        return true;
    }
    return false;
}

int Handler::player_collision(std::list<Object_dynamic>::iterator &dyn) {
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(dyn->get_center().x, dyn->get_size().length, player.get_center().x, player.get_size().length) &&
       cmp(dyn->get_center().y, dyn->get_size().width, player.get_center().y, player.get_size().width) &&
       cmp(dyn->get_center().z, dyn->get_size().height, player.get_center().z, player.get_size().height)) {
        unsigned int range = abs(dyn->get_center().x - player.get_center().x);
        unsigned int characteristics = player.get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(dyn->get_center().y - player.get_center().y);
        characteristics = player.get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(dyn->get_center().z - player.get_center().z);
        characteristics = player.get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision(std::list<Object_dynamic>::iterator &first, std::list<Object_static>::iterator &second) {
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first->get_center().x, first->get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(first->get_center().y, first->get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(first->get_center().z, first->get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(first->get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(first->get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(first->get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision_player(std::list<Object_static>::iterator &second) {
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(player.get_center().x, player.get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(player.get_center().y, player.get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(player.get_center().z, player.get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(player.get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(player.get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(player.get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision_act(std::list<Object_dynamic>::iterator &first, std::list<Object_activated>::iterator &second) {
    /*if(second->get_elem_type() == DOOR && second.status == active) { //Не знаю реализацию, надо пофиксить
        return false;
    }*/
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first->get_center().x, first->get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(first->get_center().y, first->get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(first->get_center().z, first->get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(first->get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(first->get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(first->get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision_act_player(std::list<Object_activated>::iterator &second) {
    /*if(second->get_elem_type() == DOOR && second->status == active) { //Не знаю реализацию, надо пофиксить
        return false;
    }*/
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(player.get_center().x, player.get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(player.get_center().y, player.get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(player.get_center().z, player.get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(player.get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(player.get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(player.get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision_actr(std::list<Object_dynamic>::iterator &first, std::list<Object_activator>::iterator &second) {
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first->get_center().x, first->get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(first->get_center().y, first->get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(first->get_center().z, first->get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(first->get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(first->get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(first->get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler::collision_actr_player(std::list<Object_activator>::iterator &second) {
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(player.get_center().x, player.get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(player.get_center().y, player.get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(player.get_center().z, player.get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(player.get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            return X_COLLISION;
        }
        range = abs(player.get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            return Y_COLLISION;
        }
        range = abs(player.get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            return Z_COLLISION;
        }
    }
    return false;
}

void Handler::position_change(std::list<Object_dynamic>::iterator &dyn) {
    int col_type = 0;
    auto el = dyn;
    el++;
    for(el; el != dyn_elems.end(); el++) {
        if(collision_dyn(dyn, el)) {
            coll_speed_change_dyn(dyn, el);
        }
    }
    for(auto k = stat_elems.begin(); k != stat_elems.end(); k++) {
        col_type = collision(dyn, k);
        if(col_type) {
            coll_speed_change(dyn, col_type);
        }
    }
    for(auto k = act_elems.begin(); k != act_elems.end(); k++) {
        col_type = collision_act(dyn, k);
        if(col_type) {
            coll_speed_change(dyn, col_type);
        }
    }
    for(auto k = actr_elems.begin(); k != actr_elems.end(); k++) {
        col_type = collision_actr(dyn, k);
        if(col_type) {
            coll_speed_change(dyn, col_type);
        }
    }
    Point new_center = {0,0,0};
    new_center.x = dyn->get_center().x + dyn->get_speed().x * passed_time;
    new_center.y = dyn->get_center().y + dyn->get_speed().y * passed_time;
    new_center.z = dyn->get_center().z + dyn->get_speed().z * passed_time;
    dyn->set_center(new_center);
    default_speed_change(dyn);
}

void Handler::player_speed_change() {
    glm::vec3 new_speed = {0,0,0};
    glm::vec3 w_speed = {0,0,0};
    glm::vec3 a_speed = {0,0,0};
    glm::vec3 s_speed = {0,0,0};
    glm::vec3 d_speed = {0,0,0};
    /*if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
        w_speed.x = PLAYER_SPEED * camera.x;
        w_speed.y = PLAYER_SPEED * camera.y;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
        s_speed.x = -PLAYER_SPEED * camera.x;
        s_speed.y = -PLAYER_SPEED * camera.y;
    }
    glm::vec3 camera_normal = glm::rotate(camera, glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
        a_speed.x = PLAYER_SPEED * camera_normal.x;
        a_speed.y = PLAYER_SPEED * camera_normal.y;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
        d_speed.x = -PLAYER_SPEED * camera_normal.x;
        d_speed.y = -PLAYER_SPEED * camera_normal.y;
    }
    new_speed = w_speed + s_speed + a_speed + d_speed;
    if(!player.get_on_floor()) {
        new_speed.z = player.get_speed().z - Z_ACCELERATION * passed_time;
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS && player.get_on_floor()) {
        new_speed.z = PLAYER_SPEED;
        player.set_on_floor(false);
    }*/
    player.set_speed(new_speed);
}

bool Handler::look_at(std::list<Object_dynamic>::iterator &dyn) {
    glm::vec3 distant = {0,0,0};
    distant.x = -player.get_center().x + dyn->get_center().x;
    distant.y = -player.get_center().y + dyn->get_center().y;
    distant.z = -player.get_center().z + dyn->get_center().z;
    if(glm::length(distant) < PLAYER_RANGE && glm::degrees(glm::angle(camera, distant)) < 75.0f) {
        return true;
    }
    return false;

}

void Handler::player_update() {
    player_speed_change();
    Point old_center = player.get_center();
    Point new_center;
    new_center.x = player.get_speed().x * passed_time + player.get_center().x;
    new_center.y = player.get_speed().y * passed_time + player.get_center().y;
    new_center.z = player.get_speed().z * passed_time + player.get_center().z;
    player.set_center(new_center);
    int coll_type = 0;
    auto el = dyn_elems.begin();
    for(el; el != dyn_elems.end(); el++) {
        /*if(glfwGetKey(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && look_at(el) && !player.get_status()) {
            player.take_object(el);
           el.pop;
        }*/
        coll_type = player_collision(el);
        if(coll_type) {
            coll_speed_player(el, coll_type);
        }
    }
    player.set_on_floor(false); //если игрок упал с чего-то, то он не зайдет в Z_COLLISION=>обработка падения
    auto st = stat_elems.begin();
    for(st; st != stat_elems.end(); st++) {
        coll_type = collision_player(st);
        if(coll_type == X_COLLISION) {
            player.get_center().x = old_center.x;
        }
        if(coll_type == Y_COLLISION) {
            player.get_center().y = old_center.y;
        }
        if(coll_type == Z_COLLISION) {
            player.get_center().z = st->get_center().z + st->get_size().height / 2
                                    + player.get_size().height / 2;
            player.set_on_floor(true);
        }
    }
    //Не уверен насчет этого, хз, как выглядят элементы фич
    auto ac = act_elems.begin();
    for(ac; ac!= act_elems.end(); ac++) {
        coll_type = collision_act_player(ac);
        if(coll_type == X_COLLISION) {
            player.get_center().x = old_center.x;
        }
        if(coll_type == Y_COLLISION) {
            player.get_center().y = old_center.y;
        }
        if(coll_type == Z_COLLISION) {
            player.get_center().z = ac->get_center().z + ac->get_size().height / 2
                                    + player.get_size().height / 2;
            player.set_on_floor(true);
        }
    }
    auto acr = actr_elems.begin();
    for(acr; acr != actr_elems.end(); acr++) {
        coll_type = collision_actr_player(acr);
        if(coll_type == X_COLLISION) {
            player.get_center().x = old_center.x;
        }
        if(coll_type == Y_COLLISION) {
            player.get_center().y = old_center.y;
        }
        if(coll_type == Z_COLLISION) {
            player.get_center().z = acr->get_center().z + acr->get_size().height / 2
                                    + player.get_size().height / 2;
            player.set_on_floor(true);
        }
    }
    /*if(glfwGetKey(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && player.get_status()) {
        std::list<Object_dynamic>::iterator new_elem = player.drop_object();
        glm::vec3 speed ={0,0,0};
        Point center = {0,0,0};
        center.x = player.get_center().x + camera.x * RANGE_DROP;
        center.y = player.get_center().y + camera.y * RANGE_DROP;
        center.z = player.get_center().z + camera.z * RANGE_DROP;
        new_elem->set_speed(speed);
        new_elem->set_center(center);
        dyn_elems.push_back(*new_elem);
    }*/
}

void Handler::update(float ps_time, glm::vec3& cam) {
    camera = cam;
    passed_time = ps_time;
    player_update();
    auto el = dyn_elems.begin();
    for(el; el != dyn_elems.end(); el++) {
        position_change(el);
    }
}