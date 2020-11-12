#ifndef PROJECT_QUIZ_FIGURE_RENDER_OBJECTS_H
#define PROJECT_QUIZ_FIGURE_RENDER_OBJECTS_H

#endif //PROJECT_QUIZ_FIGURE_RENDER_OBJECTS_H

class Render_objects {
public:
    std::vector<Object_dynamic> dyn_elems;
    std::vector<Object_static> stat_elems;
    std::vector<Object_activated> act_elems;
    GLFWwindow my_window;
    std::vector<std::String> my_models_paths;

    void render();
    Render_objects();
    ~Render_objects();
};