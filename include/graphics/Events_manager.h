#ifndef PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H
#define PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H

#include <map>
#include <iostream>
#include "Camera_class.h"
#include "utils.h"

#include <GLFW/glfw3.h>

class Events_manager {
private:
    Camera* _camera_ptr;
    float _lastX = SCR_WIDTH / 2.f;
    float _lastY = SCR_HEIGHT / 2.f;
    bool _firstMouse = true;
    std::map <std::string, bool> prev_control_tools;
    void change_state(std::string key);
public:
    std::map <std::string, bool> control_tools = {{"Flashlight", 0},
                                                  {"Flight", 0},
                                                  {"Carcass", 0}};
    //Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
    void processInput(GLFWwindow *window, float delta_time);  //delta_time - для движения, lastX, lastY, firstMouse - для мышки(движение камерой)
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow* window);
    Events_manager();
    Events_manager(Camera* camera_ptr);
};

#endif //PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H