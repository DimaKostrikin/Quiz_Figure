#ifndef PROJECT_QUIZ_FIGURE_RENDER_MANAGER_H
#define PROJECT_QUIZ_FIGURE_RENDER_MANAGER_H

#include <list>

#include "Features_lib/Objects.h"

class Render_manager {
public:
    //тайминги для рассчет движения
    float deltaTime = 0.0f;	// время между текущим и последним кадрами
    float lastFrame = 0.0f; // время последнего кадра
    std::list<Object_dynamic>& obj_dyn;
    std::list<Object_static>& obj_stat;
    std::list<Object_activated>& obj_acted;
    std::list<Object_activator>& obj_actor;
    std::list<Object_influence>& obj_infl;

    Camera camera;
    Events_manager ev_manager;
//    Render_manager();
    Render_manager(std::list<Object_dynamic>& object_dyn, std::list<Object_static>& object_stat,
            std::list<Object_activated>& object_acted, std::list<Object_activator>& object_actor, std::list<Object_influence>& object_infl);
    static bool preparation(GLFWwindow* window);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void render(Shader cur_shader_prog, Model cur_model, std::vector <Point_light> point_lights, bool is_light_source = false);
    void setup_camera();
    void setup_camera(glm::vec3 position);
    void setup_camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    void setup_camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    void process_render(GLFWwindow* window, Shader shader, std::vector <Point_light> point_lights);
    void process_render(GLFWwindow* window, Shader shader, std::vector <Point_light> point_lights, std::vector <Model> models_vec);
    void clear();

    Camera &get_camera();

private:
};

#endif //PROJECT_QUIZ_FIGURE_RENDER_MANAGER_H
