#ifndef HANDLER_FEATURE_H
#define HANDLER_FEATURE_H
#include <list>
#include "Features_lib/Objects.h"

class Handler_feature {
public:
    static Handler_feature& instance(std::list<Object_activated>& in_acted,
                                     std::list<Object_activator>& in_actor,
                                     std::list<Object_dynamic>& in_dyn,
                                     std::list<Object_influence>& in_infl,
                                     Player& pl);
    void do_logic(const double &elapsed_time);
    bool get_flag() const;

private:
    Handler_feature(std::list<Object_activated>& in_acted,
                    std::list<Object_activator>& in_actor,
                    std::list<Object_dynamic>& in_dyn,
                    std::list<Object_influence>& in_infl,
                    Player& pl);
    Handler_feature(Handler_feature const&);
    Handler_feature& operator=(Handler_feature const&);
    void action(std::list<Object_dynamic>::iterator& obj_d, std::list<Object_activator>::iterator& obj_a, const double &elapsed_time);

    bool is_near();

private:
    std::list<Object_activated>& obj_acted;
    std::list<Object_activator>& obj_actor;
    std::list<Object_dynamic>& obj_dyn;
    std::list<Object_influence>& obj_infl;
    Player& player;
    bool flag_win;
};


#endif  // HANDLER_FEATURE_H
