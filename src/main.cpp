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

    Render_manager render_mng;

    //задаем начальную позицию камеры(игрка)
    render_mng.setup_camera(glm::vec3(0.f, 0.5f, 3.f));

    //кроме позиции можно также задать начальное направления взгляда:
    //render_mng.camera.set_yaw_pitch(90.f, 45.f);  //yaw - поворот влево-вправо, pitch - вверх-вниз. Все в градусах.

    //подготовка к отрисовке
    if (!render_mng.preparation(window)) return -1;  //если возникли ошибки, то возвращает 0

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

    for (size_t i = 0; i < 4; ++i) {
        point_lights.push_back(Point_light(pointLightPositions[i]));
    }

    //вектор моделей (пока вручную)
    std::vector <Model> models_vec;
    models_vec.push_back(Model ("../resources/objects/test/test_cube.obj"));
    models_vec.push_back(Model ("../resources/objects/white_cube/white_cube.obj"));
    models_vec.push_back(Model ("../resources/objects/white_cube/white_cube.obj"));
    models_vec.push_back(Model ("../resources/objects/white_cube/white_cube.obj"));
    models_vec.push_back(Model ("../resources/objects/white_cube/white_cube.obj"));

    //задаем координаты моделям-лампочкам(совпадают с кординатами источников света)
    for (unsigned int i = 1; i < 5; i++) {
        models_vec[i].set_xpos(pointLightPositions[i - 1].x);
        models_vec[i].set_ypos(pointLightPositions[i - 1].y);
        models_vec[i].set_zpos(pointLightPositions[i - 1].z);
    }

    // Цикл рендеринга
    while(!glfwWindowShouldClose(window)) {
        render_mng.process_render(window, ourShader, point_lights, models_vec);
    }

    //очищаем
    render_mng.clear();

    return 0;
}