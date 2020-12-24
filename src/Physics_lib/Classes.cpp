#include "Physics_lib/classes.h"


#define SPEED_ERROR 100
#define X_COLLISION 1
#define Y_COLLISION 2
#define Z_COLLISION 3



//Обработчик

Handler_physics::Handler_physics(std::list<Object_dynamic> &d, std::list<Object_static> &s, std::list<Object_activated> &a,
                 std::list<Object_activator> &ar, Player &p, glm::vec3& cam, GLFWwindow *window) :
        player(p), dyn_elems(d), stat_elems(s), act_elems(a), actr_elems(ar), camera(cam), passed_time(0), window(window) {}

void Handler_physics::take_object(std::list<Object_dynamic>::iterator &object_taken) {
    player.set_status(true);
    object_taken->set_on_floor(false);
    object_taken->set_taken(true);
}

void Handler_physics::drop_object(std::list<Object_dynamic>::iterator &object_dropped) {
    player.set_status(false);
    object_dropped->set_taken(false);
}

void Handler_physics::default_speed_change(std::list<Object_dynamic>::iterator &dyn) {
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


void Handler_physics::coll_speed_change_dyn(std::list<Object_dynamic>::iterator &dyn1, std::list<Object_dynamic>::iterator &dyn2) {
    glm::vec2 xy1 = {dyn1->get_speed().x, dyn1->get_speed().y};
    glm::vec2 norm_xy1 = glm::normalize(xy1);
    glm::vec2 xy2 = {dyn2->get_speed().x, dyn2->get_speed().y};
    glm::vec2 norm_xy2 = glm::normalize(xy2);
    glm::vec2 xy_dist_1 = {dyn2->get_center().x - dyn1->get_center().x, dyn2->get_center().y - dyn1->get_center().y};
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

void Handler_physics::coll_speed_change(std::list<Object_dynamic>::iterator &dyn, int coll_type) {
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

void Handler_physics::coll_speed_player(std::list<Object_dynamic>::iterator &dyn, int coll_type) {
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

bool Handler_physics::collision_dyn(std::list<Object_dynamic>::iterator &first, std::list<Object_dynamic>::iterator &second) {
    float range = first->get_size().height / 2 + second->get_size().height / 2;
    if(sqrt(pow(first->get_center().x - second->get_center().x, 2) + pow(first->get_center().y - second->get_center().y, 2)
            + pow(first->get_center().z - second->get_center().z, 2)) < range) {
        glm::vec3 distance ={0,0,0};
        distance.x = -second->get_center().x + first->get_center().x;
        distance.y = -second->get_center().y + first->get_center().y;
        distance.z = -second->get_center().z + first->get_center().z;
        glm::vec3 set_dist = glm::normalize(distance) * range;
        Point new_center = {0,0,0};
        new_center.x = second->get_center().x + set_dist.x;
        new_center.y = second->get_center().y + set_dist.y;
        new_center.z = second->get_center().z + set_dist.z;
        first->set_center(new_center);
        return true;
    }
    return false;
}

int Handler_physics::player_collision(std::list<Object_dynamic>::iterator &dyn) {
    Point new_center = dyn->get_center();
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(dyn->get_center().x, dyn->get_size().length, player.get_center().x, player.get_size().length) &&
       cmp(dyn->get_center().y, dyn->get_size().width, player.get_center().y, player.get_size().width) &&
       cmp(dyn->get_center().z, dyn->get_size().height, player.get_center().z, player.get_size().height)) {
        unsigned int range = abs(dyn->get_center().x - player.get_center().x);
        unsigned int characteristics = player.get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            if(player.get_center().x - dyn->get_center().x > 0) {
                new_center.x = player.get_center().x - player.get_size().length / 2 - dyn->get_size().length / 2;
                dyn->set_center(new_center);
            }
            else {
                new_center.x = player.get_center().x + player.get_size().length / 2 + dyn->get_size().length / 2;
                dyn->set_center(new_center);
            }
            return X_COLLISION;
        }
        range = abs(dyn->get_center().y - player.get_center().y);
        characteristics = player.get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            if(player.get_center().y - dyn->get_center().y > 0) {
                new_center.y = player.get_center().y - player.get_size().width / 2 - dyn->get_size().width / 2;
                dyn->set_center(new_center);
            }
            else {
                new_center.y = player.get_center().y + player.get_size().width / 2 + dyn->get_size().width / 2;
                dyn->set_center(new_center);
            }
            return Y_COLLISION;
        }
        range = abs(dyn->get_center().z - player.get_center().z);
        characteristics = player.get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            if(player.get_center().z - dyn->get_center().z > 0) {
                new_center.z = player.get_center().z - player.get_size().height / 2 - dyn->get_size().height / 2;
                dyn->set_center(new_center);
            }
            else {
                new_center.z = player.get_center().z + player.get_size().height / 2 + dyn->get_size().height / 2;
                dyn->set_center(new_center);
            }
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler_physics::collision(std::list<Object_dynamic>::iterator &first, std::list<Object_static>::iterator &second) {
    Point new_center = first->get_center();
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first->get_center().x, first->get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(first->get_center().y, first->get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(first->get_center().z, first->get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(first->get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            if(second->get_center().x - first->get_center().x > 0) {
                new_center.x = second->get_center().x - second->get_size().length / 2 - first->get_size().length / 2;
                first->set_center(new_center);
            }
            else {
                new_center.x = second->get_center().x + second->get_size().length / 2 + first->get_size().length / 2;
                first->set_center(new_center);
            }
            return X_COLLISION;
        }
        range = abs(first->get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            if(second->get_center().y - first->get_center().y > 0) {
                new_center.y = second->get_center().y - second->get_size().width / 2 - first->get_size().width / 2;
                first->set_center(new_center);
            }
            else {
                new_center.y = second->get_center().y + second->get_size().width / 2 + first->get_size().width / 2;
                first->set_center(new_center);
            }
            return Y_COLLISION;
        }
        range = abs(first->get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            if(second->get_center().z - first->get_center().z > 0) {
                new_center.z = second->get_center().z - second->get_size().height / 2 - first->get_size().height / 2;
                first->set_center(new_center);
            }
            else {
                new_center.z = second->get_center().z + second->get_size().height / 2 + first->get_size().height / 2;
                first->set_center(new_center);
            }
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler_physics::collision_player(std::list<Object_static>::iterator &second) {
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

int Handler_physics::collision_act(std::list<Object_dynamic>::iterator &first, std::list<Object_activated>::iterator &second) {
    if(second->get_elem_type() == DOOR && second->is_activated()) { //Не знаю реализацию, надо пофиксить
        return false;
    }
    Point new_center = first->get_center();
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first->get_center().x, first->get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(first->get_center().y, first->get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(first->get_center().z, first->get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(first->get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            if(second->get_center().x - first->get_center().x > 0) {
                new_center.x = second->get_center().x - second->get_size().length / 2 - first->get_size().length / 2;
                first->set_center(new_center);
            }
            else {
                new_center.x = second->get_center().x + second->get_size().length / 2 + first->get_size().length / 2;
                first->set_center(new_center);
            }
            return X_COLLISION;
        }
        range = abs(first->get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            if(second->get_center().y - first->get_center().y > 0) {
                new_center.y = second->get_center().y - second->get_size().width / 2 - first->get_size().width / 2;
                first->set_center(new_center);
            }
            else {
                new_center.y = second->get_center().y + second->get_size().width / 2 + first->get_size().width / 2;
                first->set_center(new_center);
            }
            return Y_COLLISION;
        }
        range = abs(first->get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            if(second->get_center().z - first->get_center().z > 0) {
                new_center.z = second->get_center().z - second->get_size().height / 2 - first->get_size().height / 2;
                first->set_center(new_center);
            }
            else {
                new_center.z = second->get_center().z + second->get_size().height / 2 + first->get_size().height / 2;
                first->set_center(new_center);
            }
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler_physics::collision_act_player(std::list<Object_activated>::iterator &second) {
    if(second->get_elem_type() == DOOR && second->is_activated()) { //Не знаю реализацию, надо пофиксить
        return false;
    }
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

int Handler_physics::collision_actr(std::list<Object_dynamic>::iterator &first, std::list<Object_activator>::iterator &second) {
    Point new_center = first->get_center();
    auto cmp = [](int x, int y, int a, int b) {return (x - y / 2 < a + b / 2) && (x + y / 2 > a - b / 2);};
    if(cmp(first->get_center().x, first->get_size().length, second->get_center().x, second->get_size().length) &&
       cmp(first->get_center().y, first->get_size().width, second->get_center().y, second->get_size().width) &&
       cmp(first->get_center().z, first->get_size().height, second->get_center().z, second->get_size().height)) {
        unsigned int range = abs(first->get_center().x - second->get_center().x);
        unsigned int characteristics = second->get_size().length / 2;//Длина всегда по x
        if (range > characteristics) {
            if(second->get_center().x - first->get_center().x > 0) {
                new_center.x = second->get_center().x - second->get_size().length / 2 - first->get_size().length / 2;
                first->set_center(new_center);
            }
            else {
                new_center.x = second->get_center().x + second->get_size().length / 2 + first->get_size().length / 2;
                first->set_center(new_center);
            }
            return X_COLLISION;
        }
        range = abs(first->get_center().y - second->get_center().y);
        characteristics = second->get_size().width / 2;//Ширина всегда по y
        if (range > characteristics) {
            if(second->get_center().y - first->get_center().y > 0) {
                new_center.y = second->get_center().y - second->get_size().width / 2 - first->get_size().width / 2;
                first->set_center(new_center);
            }
            else {
                new_center.y = second->get_center().y + second->get_size().width / 2 + first->get_size().width / 2;
                first->set_center(new_center);
            }
            return Y_COLLISION;
        }
        range = abs(first->get_center().z - second->get_center().z);
        characteristics = second->get_size().height / 2;//Высота всегда по z
        if (range > characteristics) {
            if(second->get_center().z - first->get_center().z > 0) {
                new_center.z = second->get_center().z - second->get_size().height / 2 - first->get_size().height / 2;
                first->set_center(new_center);
            }
            else {
                new_center.z = second->get_center().z + second->get_size().height / 2 + first->get_size().height / 2;
                first->set_center(new_center);
            }
            return Z_COLLISION;
        }
    }
    return false;
}

int Handler_physics::collision_actr_player(std::list<Object_activator>::iterator &second) {
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

void Handler_physics::position_change(std::list<Object_dynamic>::iterator &dyn) {
    int col_type = 0;
    auto el = dyn;
    el++;
    for(el; el != dyn_elems.end(); el++) {
        if(collision_dyn(dyn, el)) {
            if(dyn->get_taken()) {
                drop_object(dyn);
            }
            coll_speed_change_dyn(dyn, el);
        }
    }
    for(auto k = stat_elems.begin(); k != stat_elems.end(); k++) {
        col_type = collision(dyn, k);
        if(col_type) {
            if(dyn->get_taken()) {
                drop_object(dyn);
            }
            coll_speed_change(dyn, col_type);
        }
    }
    for(auto k = act_elems.begin(); k != act_elems.end(); k++) {
        col_type = collision_act(dyn, k);
        if(col_type) {
            if(dyn->get_taken()) {
                drop_object(dyn);
            }
            coll_speed_change(dyn, col_type);
        }
    }
    for(auto k = actr_elems.begin(); k != actr_elems.end(); k++) {
        col_type = collision_actr(dyn, k);
        if(col_type) {
            if(dyn->get_taken()) {
                drop_object(dyn);
            }
            coll_speed_change(dyn, col_type);
        }
    }
    Point new_center = {0,0,0};
    if(dyn->get_taken()) {
        new_center.x = player.get_center().x + camera.x * PLAYER_RANGE;
        new_center.y = player.get_center().y + camera.y * PLAYER_RANGE;
        new_center.z = player.get_center().z + camera.z * PLAYER_RANGE;
    }
    else {
        new_center.x = dyn->get_center().x + dyn->get_speed().x * passed_time;
        new_center.y = dyn->get_center().y + dyn->get_speed().y * passed_time;
        new_center.z = dyn->get_center().z + dyn->get_speed().z * passed_time;
    }
    dyn->set_center(new_center);
    if(dyn->get_taken()) {
        glm::vec3 new_speed = {0,0,0};
        dyn->set_speed(new_speed);
    }
    else {
        default_speed_change(dyn);
    }
}

void Handler_physics::player_speed_change() {
    glm::vec3 new_speed = {0,0,0};
    glm::vec3 w_speed = {0,0,0};
    glm::vec3 a_speed = {0,0,0};
    glm::vec3 s_speed = {0,0,0};
    glm::vec3 d_speed = {0,0,0};




    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
        w_speed.x = PLAYER_SPEED * camera.x;
        w_speed.y = PLAYER_SPEED * camera.z;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
        s_speed.x = -PLAYER_SPEED * camera.x;
        s_speed.y = -PLAYER_SPEED * camera.z;
    }
    glm::vec3 camera_normal = glm::rotate(camera, glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
        a_speed.x = PLAYER_SPEED * camera_normal.x;
        a_speed.y = PLAYER_SPEED * camera_normal.z;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
        d_speed.x = -PLAYER_SPEED * camera_normal.x;
        d_speed.y = -PLAYER_SPEED * camera_normal.z;
    }
    new_speed = w_speed + s_speed + a_speed + d_speed;
    /*if(!player.get_on_floor()) {
        new_speed.z = player.get_speed().z - Z_ACCELERATION * passed_time;
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS && player.get_on_floor()) {
        new_speed.z = PLAYER_SPEED;
        player.set_on_floor(false);
    }*/
    
    player.set_speed(new_speed);
}

bool Handler_physics::look_at(std::list<Object_dynamic>::iterator &dyn) {
    glm::vec3 distant = {0,0,0};
    distant.x = -player.get_center().x + dyn->get_center().x;
    distant.y = -player.get_center().y + dyn->get_center().y;
    distant.z = -player.get_center().z + dyn->get_center().z;
    if(glm::length(distant) < PLAYER_RANGE && glm::degrees(glm::angle(camera, distant)) < 75.0f) {
        return true;
    }
    return false;

}

void Handler_physics::player_update() {
    player_speed_change();
    Point old_center = player.get_center();
    Point new_center;
    new_center.x = player.get_speed().x * passed_time + player.get_center().x;
    new_center.y = player.get_speed().y * passed_time + player.get_center().y;
    new_center.z = player.get_speed().z * passed_time + player.get_center().z;
    player.set_center(new_center);
    
    if(glfwGetKey(window,GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && player.get_status()) {  // Тут точно != ?
        auto els = dyn_elems.begin();
        for(els; els != dyn_elems.end(); els++){
            drop_object(els);
        }
    }
    int coll_type = 0;
    auto el = dyn_elems.begin();
    for(el; el != dyn_elems.end(); el++) {
        if(glfwGetKey(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && look_at(el) && !player.get_status()) {
            take_object(el);
        }
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
}

void Handler_physics::update(double ps_time) {
    passed_time = ps_time;
    player_update();
    auto el = dyn_elems.begin();
    for(el; el != dyn_elems.end(); el++) {
        position_change(el);
    }
    std::cout << "camera " << camera.x << " " << camera.y << " " << camera.z << std::endl;
    std::cout << "player speed " << player.get_speed().x << " " << player.get_speed().y << " " << player.get_speed().z << std::endl;
}