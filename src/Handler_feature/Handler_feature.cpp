#include "Handler_feature/Handler_feature.h"
#include "Objects/Objects.h"
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

void Handler_feature::do_logic() {
    auto it_acted = obj_acted.begin();
    auto it_actor = obj_actor.begin();
    auto it_dyn = obj_dyn.begin();

    for (it_acted; it_acted != obj_acted.end(); it_acted++) {
        for (it_actor; it_actor != obj_actor.end(); it_actor++) {
            for (it_dyn; it_dyn != obj_dyn.end(); it_dyn++) {
                if (is_near(it_dyn, it_actor)) {
                    it_actor->activate_linked_object();
                } else {
                    it_actor->deactivate_linked_object();
                }
            }
        }
    }
}

bool Handler_feature::is_near(std::list<Object_dynamic>::iterator &obj_d, std::list<Object_activator>::iterator &obj_a) {
    if (obj_a->get_elem_type() == BUTTON) {
        int diff_x = obj_d->get_center().x - obj_a->get_center().x;
        int diff_y = obj_d->get_center().y - obj_a->get_center().y;
        int diff_z = abs(obj_d->get_center().z - obj_a->get_center().z);


        int event_radius = sqrt(diff_x * diff_x + diff_y * diff_y);
        std::cout << "event_radius is: " << event_radius << std::endl;
        int activate_radius = 100;

        if (event_radius < activate_radius && diff_z < 100) {
            return true;
        }
        return false;
    }
}


