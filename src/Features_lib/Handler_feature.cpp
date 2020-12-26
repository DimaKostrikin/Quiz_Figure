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
    for (auto it_actor = obj_actor.begin(); it_actor != obj_actor.end(); ++it_actor) {
        for (auto it_dyn = obj_dyn.begin(); it_dyn != obj_dyn.end(); ++it_dyn) {
            action(it_dyn, it_actor, elapsed_time);
        }
    }

}

void Handler_feature::action(std::list<Object_dynamic>::iterator &obj_d, std::list<Object_activator>::iterator &obj_a, const double &elapsed_time) {
    float diff_x_obj = obj_d->get_center().x - obj_a->get_center().x;  // Расстояние до кнопки
    float diff_y_obj = obj_d->get_center().y - obj_a->get_center().y;
    float diff_z_obj = abs(obj_d->get_center().z - obj_a->get_center().z);

    float diff_x_pl = player.get_center().x - obj_a->get_center().x;  // Расстояние до игрока
    float diff_y_pl = player.get_center().y - obj_a->get_center().y;
    float diff_z_pl = abs(player.get_center().z - obj_a->get_center().z);

    float event_radius_obj = sqrt(diff_x_obj * diff_x_obj + diff_y_obj * diff_y_obj);
    float event_radius_pl = sqrt(diff_x_pl * diff_x_pl + diff_y_pl * diff_y_pl);


    if (obj_a->get_elem_type() == BUTTON) {  // Обработка нажатия на кнопку
        float a_radius = 1.1;  // Радиусы активации, зависящие от типа элемента. Настраиваемые.
        float a_height = 1.1;


        if ((event_radius_obj < a_radius && diff_z_obj < a_height) || (event_radius_pl < a_radius && diff_z_pl < a_height)) {
            obj_a->activate_linked_object();
        } else {
            obj_a->deactivate_linked_object();
        }
    }

    if (obj_a->get_elem_type() == FAN) {  // Обработка попадания в зону вентилятора
        float a_radius = obj_a->get_size().r * 1.1;

        float a_height = 5;
        float acceleration_coeff = 0;

        if (event_radius_obj < a_radius && diff_z_obj < a_height) {
            acceleration_coeff = (a_height - diff_z_obj) / a_height;
            obj_d->get_speed().z += acceleration_coeff * elapsed_time * 10; // TODO коэффициент скорости отладить
        }

        if (event_radius_pl < a_radius && diff_z_pl < a_height) {
            acceleration_coeff = (a_height - diff_z_pl) / a_height;
            player.get_speed().z += acceleration_coeff  * elapsed_time * 10;// TODO коэффициент скорости отладить
        }
    }

    if (obj_a->get_elem_type() == JUMPER) {  // TODO сделать функции определяющие расстояния
        float a_radius = obj_a->get_size().r + 0.05;  // Радиусы активации, зависящие от типа элемента. Настраиваемые.
        float a_height = obj_a->get_size().z + 0.4;

        float changing_speed = 1.3;

        if (event_radius_pl < a_radius && diff_z_pl < a_height) {

            player.set_on_floor(false);
            player.get_speed().z = changing_speed * abs(player.get_speed().z);
            player.get_speed().x = changing_speed / 4;
        }
    }

    if (obj_a->get_elem_type() == TELEPORT_IN) {
        float a_radius = 1.1;  // TODO поменять радиусы
        float a_height = 1.1;


        if (event_radius_obj < a_radius && diff_z_obj < a_height) {
            obj_d->get_center().x = obj_a->get_linked_object()->get_center().x;
            obj_d->get_center().y = obj_a->get_linked_object()->get_center().y;
            obj_d->get_center().z = obj_a->get_linked_object()->get_center().z + obj_a->get_linked_object()->get_size().z;
        }

        if (event_radius_pl < a_radius && diff_z_pl < a_height) {
            player.get_center().x = obj_a->get_linked_object()->get_center().x;
            player.get_center().y = obj_a->get_linked_object()->get_center().y;
            player.get_center().z = obj_a->get_linked_object()->get_center().z + obj_a->get_linked_object()->get_size().z;
        }
    }
}

