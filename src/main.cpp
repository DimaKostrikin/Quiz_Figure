#include <iostream>

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

#include "Model_class.h"

#include "Point_light.h"

#include "Render_manager.h"

#include "utils.h"

int main() {
    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", NULL, NULL);

    //==================================================================================


    //подготовка к отрисовке
    if (!Render_manager::preparation(window)) return -1;  //если возникли ошибки, то возвращает 0

    std::list<Object_dynamic> obj_dyn;
    std::list<Object_static> obj_stat;
    std::list<Object_activated> obj_acted;
    std::list<Object_activator> obj_actor;
    std::list<Object_influence> obj_infl;

    Point point = {0,0,0};
    Size size = {0,0,0};

    Object_static my_static(WALL, point, size);

    obj_stat.push_back(my_static);


    Render_manager render_mng(obj_dyn, obj_stat, obj_acted, obj_actor, obj_infl);

    //задаем начальную позицию камеры(игрка)
    render_mng.setup_camera(glm::vec3(0.f, 0.5f, 3.f));

    //кроме позиции можно также задать начальное направления взгляда:
    //render_mng.camera.set_yaw_pitch(90.f, 45.f);  //yaw - поворот влево-вправо, pitch - вверх-вниз. Все в градусах.

    // Компилирование шейдерной программы из файлов
    Shader ourShader("../Shader_files/shader.vs", "../Shader_files/shader.fs");

    //заполняем вектор источников света вручную(для примера, пока не объединили код)
    std::vector <Point_light> point_lights;

    glm::vec3 pointLightPositions[] = {
            glm::vec3( -3.0f,  1.0f,  5.0f),
            glm::vec3( -5.0f, 1.0f, 5.0f),
            glm::vec3(-5.0f,  1.0f, 3.0f),
            glm::vec3( -5.0f,  1.0f, 1.0f)
    };

    //зполняем вектор источников света значениями
    for (size_t i = 0; i < 4; ++i) {
        point_lights.push_back(Point_light(pointLightPositions[i]));
    }


    // Цикл рендеринга
    while(!glfwWindowShouldClose(window)) {
        render_mng.process_render(window, ourShader, point_lights);
    }

    //очищаем
    render_mng.clear();

    return 0;
}