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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);
void render(Shader cur_shader_prog, Model cur_model, Events_manager ev_manager, std::vector <Point_light> point_lights, bool is_light_source = false);
bool preparation(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//тайминги
float deltaTime = 0.0f;	// время между текущим и последним кадрами
float lastFrame = 0.0f; // время последнего кадра

//для камеры
Camera camera(glm::vec3(0.0f, 0.5f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 pointLightPositions[] = {
        glm::vec3( -3.0f,  1.0f,  5.0f),
        glm::vec3( -5.0f, 1.0f, 5.0f),
        glm::vec3(-5.0f,  1.0f, 3.0f),
        glm::vec3( -5.0f,  1.0f, 1.0f)
};

Events_manager ev_manager;

std::vector <Point_light> point_lights;

int main() {
    for (size_t i = 0; i < 4; ++i) {
        point_lights.push_back(Point_light(pointLightPositions[i]));
    }

    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", NULL, NULL);

//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//    //glad: загрузка всех указателей на OpenGL-функции
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }

    if (!preparation(window)) return -1;

    // говорим stb_image.h чтобы он перевернул загруженные текстуры относительно y-оси (до загрузки модели).
//    stbi_set_flip_vertically_on_load(true);

    //включаем Z-буфер
//    glEnable(GL_DEPTH_TEST);

    // Компилирование наших шейдерных программ
    Shader ourShader("../Shader_files/shader.vs", "../Shader_files/shader.fs");

    // загрузка моделей
    Model ourModel("../resources/objects/test/test_cube.obj");
    Model white_cube_model("../resources/objects/white_cube/white_cube.obj");

//    // отрисовка в режиме каркаса
//    if (Control_tools["Carcass"]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //захват курсора
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Цикл рендеринга
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Обработка ввода
        ev_manager.processInput(window, camera, deltaTime);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // отрисовка в режиме каркаса
        if (ev_manager.get("Carcass")) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Выполнение рендеринга
        //Очищаем цветовой буфер  и Z-буфер
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render(ourShader, ourModel, ev_manager, point_lights);

        // а теперь мы отрисовывает столько ламп, сколько у нас есть точечных источников света
//        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++) {
            white_cube_model.set_xpos(pointLightPositions[i].x);
            white_cube_model.set_ypos(pointLightPositions[i].y);
            white_cube_model.set_zpos(pointLightPositions[i].z);

//            render(lampShader, white_cube_model, ev_manager);
            render(ourShader, white_cube_model, ev_manager, point_lights,true);

        }

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий Ввода/Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
//    ourShader.use();

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();

    return 0;
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или оперионной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна
    // Обратите внимание, что ширина и высота будут значительно больше, чем указано на Retina-дисплеях
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void render(Shader cur_shader_prog, Model cur_model, Events_manager ev_manager, std::vector <Point_light> point_lights, bool is_light_source)  {

    cur_shader_prog.use();

    // преобразования Вида/Проекции
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    cur_shader_prog.setMat4("projection", projection);
    cur_shader_prog.setMat4("view", view);

    // рендеринг загруженной модели
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(cur_model.get_xpos(), cur_model.get_ypos(), cur_model.get_zpos()));
    model = glm::rotate(model, glm::radians(cur_model.get_xangle()), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(cur_model.get_yangle()), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(cur_model.get_zangle()), glm::vec3(0.0, 0.0, 1.0));

    model = glm::scale(model, glm::vec3(cur_model.get_xscale(), cur_model.get_yscale(), cur_model.get_zscale()));
    cur_shader_prog.setMat4("model", model);
    cur_model.Draw(cur_shader_prog, camera, ev_manager, point_lights, is_light_source);
}

bool preparation(GLFWwindow* window) {

    //glfw: настройка окна
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    //включаем Z-буфер
    glEnable(GL_DEPTH_TEST);
}