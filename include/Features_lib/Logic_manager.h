#ifndef LOGIC_MANAGER_H
#define LOGIC_MANAGER_H
#include "Features_lib/Objects.h"
#include "Features_lib/Handler_feature.h"
#include <list>
#include "Map_editor_lib/Interface.h"
#include "Features_lib/Parser.h"
#include "Physics_lib/classes.h"
#include "Graphics_lib/Render_manager.h"
#include "Graphics_lib/utils.h"
#include "Map_editor_lib/Elements.h"
// include all features

class Logic_manager {
public:
    static Logic_manager& instance();
    void initialize();
private:
    Logic_manager() = default;
    ~Logic_manager() = default;

    GLFWwindow *window;
    int start_game(const std::string &level_path);
    void start_redactor();
    void draw_menu();
    int cursor_check();
    std::string choose_level();
};


#endif // LOGIC_MANAGER_H
