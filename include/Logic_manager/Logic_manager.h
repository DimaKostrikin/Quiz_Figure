#ifndef LOGIC_MANAGER_H
#define LOGIC_MANAGER_H
#include "Objects/Objects.h"
#include "Handler_feature/Handler_feature.h"
#include <list>
#include <GLFW/glfw3.h>
// include all features

enum {
    START,
    REDACTOR,
    EXIT,
    NOTHING
};

class Logic_manager {
public:
    static Logic_manager& instance();
    void initialize();
private:
    Logic_manager() = default;
    ~Logic_manager() = default;

    void start_game();
    void start_redactor();
    void draw_menu();
    int cursor_check();
    std::string choose_level();
};


#endif // LOGIC_MANAGER_H
