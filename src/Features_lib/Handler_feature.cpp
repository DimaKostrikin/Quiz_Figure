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
                is_near(it_dyn, it_actor, elapsed_time);
            }
        }
    }
}

bool Handler_feature::is_near(std::list<Object_dynamic>::iterator &obj_d, std::list<Object_activator>::iterator &obj_a, const double &elapsed_time) {
    if (obj_a->get_elem_type() == BUTTON) {  // Обработка нажатия на кнопку
        int diff_x_obj = obj_d->get_center().x - obj_a->get_center().x;  // Расстояние до кнопки
        int diff_y_obj = obj_d->get_center().y - obj_a->get_center().y;
        int diff_z_obj = abs(obj_d->get_center().z - obj_a->get_center().z);

        int diff_x_pl = player.get_center().x - obj_a->get_center().x;  // Расстояние до игрока
        int diff_y_pl = obj_d->get_center().y - obj_a->get_center().y;
        int diff_z_pl = abs(obj_d->get_center().z - obj_a->get_center().z);

        int diff_x = std::min(diff_x_obj, diff_x_pl);  // Вычисление минимального расстояния исходя из кнопки и игрока.
        int diff_y = std::min(diff_y_obj, diff_y_pl);
        int diff_z = std::min(diff_z_obj, diff_z_pl);


        int event_radius = sqrt(diff_x * diff_x + diff_y * diff_y);
        std::cout << "event_radius is: " << event_radius << std::endl;

        int a_radius = 100;  // Радиусы активации, зависящие от типа элемента. Настраиваемые.
        int a_height = 100;

        if (event_radius < a_radius && diff_z < a_height) {
            obj_a->activate_linked_object();
        } else {
            obj_a->deactivate_linked_object();
        }
    }

    if (obj_a->get_elem_type() == FAN) {
        int diff_x = obj_d->get_center().x - obj_a->get_center().x;
        int diff_y = obj_d->get_center().y - obj_a->get_center().y;
        int diff_z = abs(obj_d->get_center().z - obj_a->get_center().z);

        int event_radius = sqrt(diff_x * diff_x + diff_y * diff_y);

        int a_radius = 1000;

        int a_height = 50000;
        if (event_radius < a_radius && diff_z < a_height) {
            int acceleration_coeff = (a_height - diff_z) / a_height;
            obj_d->get_speed().dz += acceleration_coeff * elapsed_time * 1000 ; // TODO коэффициент скорости отладить
        }
    }

    if (obj_a->get_elem_type() == JUMPER) {  // TODO сделать функции определяющие расстояния
        int diff_x_pl = player.get_center().x - obj_a->get_center().x;  // Расстояние до игрока
        int diff_y_pl = obj_d->get_center().y - obj_a->get_center().y;
        int diff_z_pl = abs(obj_d->get_center().z - obj_a->get_center().z);

        int event_radius = sqrt(diff_x_pl * diff_x_pl + diff_y_pl * diff_y_pl);

        int a_radius = 100;  // Радиусы активации, зависящие от типа элемента. Настраиваемые.
        int a_height = 100;


        int changing_speed = 10000;
        if (event_radius < a_radius && diff_z_pl < a_height) {
            player.get_speed().dz += changing_speed;
            player.get_speed().dx += changing_speed / 4;
        }


    }
}

