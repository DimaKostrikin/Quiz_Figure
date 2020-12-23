#include "Features_lib/Handler_feature.h"
#include "Features_lib/Objects.h"
#include <cmath>



Handler_feature& Handler_feature::instance(std::list<Object_activated>& in_acted,
                                           std::list<Object_activator>& in_actor,
                                           std::list<Object_dynamic>& in_dyn,
                                           std::list<Object_influence>& in_infl,
                                           Player& pl) {
    static Handler_feature h(in_acted, in_actor, in_dyn, in_infl, pl);
    return h;
}

Handler_feature::Handler_feature(std::list<Object_activated> &in_acted,
                                 std::list<Object_activator> &in_actor,
                                 std::list<Object_dynamic> &in_dyn,
                                 std::list<Object_influence>& in_infl,
                                 Player& pl)
                                 : obj_actor(in_actor), obj_acted(in_acted), obj_dyn(in_dyn), obj_infl(in_infl), player(pl) {}

void Handler_feature::do_logic(const double &elapsed_time) {
    auto it_acted = obj_acted.begin();
    auto it_actor = obj_actor.begin();
    auto it_dyn = obj_dyn.begin();

    for (it_acted; it_acted != obj_acted.end(); it_acted++) {  // TODO первый цикл не нужен похоже
        for (it_actor; it_actor != obj_actor.end(); it_actor++) {
            for (it_dyn; it_dyn != obj_dyn.end(); it_dyn++) {
                action(it_dyn, it_actor, elapsed_time);
            }
        }
    }
}

void Handler_feature::action(std::list<Object_dynamic>::iterator &obj_d, std::list<Object_activator>::iterator &obj_a, const double &elapsed_time) {
    int diff_x_obj = obj_d->get_center().x - obj_a->get_center().x;  // Расстояние до кнопки
    int diff_y_obj = obj_d->get_center().y - obj_a->get_center().y;
    int diff_z_obj = abs(obj_d->get_center().z - obj_a->get_center().z);

    int diff_x_pl = player.get_center().x - obj_a->get_center().x;  // Расстояние до игрока
    int diff_y_pl = obj_d->get_center().y - obj_a->get_center().y;
    int diff_z_pl = abs(obj_d->get_center().z - obj_a->get_center().z);

    int event_radius_obj = sqrt(diff_x_obj * diff_x_obj + diff_y_obj * diff_y_obj);
    int event_radius_pl = sqrt(diff_x_pl * diff_x_pl + diff_y_pl * diff_y_pl);

    if (obj_a->get_elem_type() == BUTTON) {  // Обработка нажатия на кнопку
        int a_radius = 100;  // Радиусы активации, зависящие от типа элемента. Настраиваемые.
        int a_height = 100;

        if ((event_radius_obj < a_radius && diff_z_obj < a_height) || (event_radius_pl < a_radius && diff_z_pl < a_height)) {
            obj_a->activate_linked_object();
        } else {
            obj_a->deactivate_linked_object();
        }
    }

    if (obj_a->get_elem_type() == FAN) {  // Обработка попадания в зону вентилятора
        int a_radius = 1000;

        int a_height = 50000;
        int acceleration_coeff = 100;

        if (event_radius_obj < a_radius && diff_z_obj < a_height) {
            acceleration_coeff = (a_height - diff_z_obj) / a_height;
            obj_d->get_speed().z += acceleration_coeff * elapsed_time * 1000 ; // TODO коэффициент скорости отладить
        }

        if (event_radius_pl < a_radius && diff_z_pl < a_height) {
            acceleration_coeff = (a_height - diff_z_pl) / a_height;
            player.get_speed().z += acceleration_coeff * elapsed_time * 1000 ; // TODO коэффициент скорости отладить
        }
    }

    if (obj_a->get_elem_type() == JUMPER) {  // TODO сделать функции определяющие расстояния
        int a_radius = 100;  // Радиусы активации, зависящие от типа элемента. Настраиваемые.
        int a_height = 100;

        int changing_speed = 10000;
        if (event_radius_obj < a_radius && diff_z_obj < a_height) {
            obj_d->get_speed().z += changing_speed;
            obj_d->get_speed().x += changing_speed / 4;
        }
    }

    if (obj_a->get_elem_type() == TELEPORT) {
        int a_radius = 100;
        int a_height = 100;


        if (event_radius_obj < a_radius && diff_z_obj < a_height) {
            obj_d->get_center().x = obj_a->get_linked_object().get_center().x;
            obj_d->get_center().y = obj_a->get_linked_object().get_center().y;
            obj_d->get_center().z = obj_a->get_linked_object().get_center().z;
        }

        if (event_radius_pl < a_radius && diff_z_pl < a_height) {
            player.get_center().x = obj_a->get_linked_object().get_center().x;
            player.get_center().y = obj_a->get_linked_object().get_center().y;
            player.get_center().z = obj_a->get_linked_object().get_center().z;
        }
    }
}

