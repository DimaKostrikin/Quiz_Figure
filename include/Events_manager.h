#ifndef PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H
#define PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H

#include <map>
//#include "glad/glad.h"
#include "Camera_class.h"

#include <GLFW/glfw3.h>

class Events_manager {
private:
    std::vector<int> events_;
    std::map <std::string, bool> control_tools = {{"Flashlight", 0},
                                                  {"Flight", 0},
                                                  {"Carcass", 0}};
    std::map <std::string, bool> prev_control_tools;
    void change_state(std::string key);

public:
    //Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
    void processInput(GLFWwindow *window, Camera &camera, float delta_time);
    //Возвращает значение control_tools по ключу
    bool get(std::string key);
    Events_manager();
};

#endif //PROJECT_QUIZ_FIGURE_EVENTS_MANAGER_H