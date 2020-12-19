#include <iostream>

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera_class.h"

#include "Model_class.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);
int moveInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//камера
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

//тайминги
float deltaTime = 0.0f;	// время между текущим и последним кадрами
float lastFrame = 0.0f; // время последнего кадра

//для камеры
Camera camera(glm::vec3(0.0f, 0.5f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

////положение источника света
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

float vertices[] = {
        // координаты          // нормали           // текстурные координаты
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

int main() {
    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // говорим stb_image.h чтобы он перевернул загруженные текстуры относительно y-оси (до загрузки модели).
//    stbi_set_flip_vertically_on_load(true);

    //включаем Z-буфер
    glEnable(GL_DEPTH_TEST);

    // Компилирование наших шейдерных программ
    Shader ourShader("../Shader_files/shader.vs", "../Shader_files/shader.fs");
    Shader lampShader("../Shader_files/lampShader.vs", "../Shader_files/lampShader.fs");

    // загрузка моделей
    Model ourModel("../resources/objects/test/test_cube.obj");

    // отрисовка в режиме каркаса
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::vec3 pointLightPositions[] = {
            glm::vec3( -3.0f,  1.0f,  5.0f),
            glm::vec3( -5.0f, 1.0f, 5.0f),
            glm::vec3(-5.0f,  1.0f, 3.0f),
            glm::vec3( -5.0f,  1.0f, 1.0f)
    };

//    unsigned int indices[] = {
//            0, 1, 3, // первый треугольник
//            1, 2, 3  // второй треугольник
//    };

    unsigned int VBO, lightVAO;

    // 1. настраиваем VAO (и VBO)
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int diffuseMap = loadTexture("../textures/box_with_metal_border.png");
    unsigned int specularMap = loadTexture("../textures/metal_border.png");

    glm::mat4 trans = glm::mat4(1.0f);

    ourShader.use();

    ourShader.setInt("material.diffuse", 0);
    ourShader.setInt("material.specular", 1);

//    ourShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
//    ourShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // немного затемним рассеянный свет
//    ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//
//    ourShader.setFloat("light.constant", 1.0f);
//    ourShader.setFloat("light.linear", 0.09f);
//    ourShader.setFloat("light.quadratic", 0.032f);

//    //камера
//    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    //матрица вида
    glm::mat4 view;

//    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Цикл рендеринга
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Обработка ввода
        processInput(window);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // Выполнение рендеринга
        //Очищаем цветовой буфер  и Z-буфер
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Убеждаемся, что активировали шейдер
//        glUseProgram(shaderProgram);

        // убеждаемся, что активировали шейдер прежде, чем настраивать uniform-переменные/объекты_рисования
        ourShader.use();
//        ourShader.setVec3("viewPos", camera.Position);
//        ourShader.setFloat("material.shininess", 32.0f);

//        // направленный свет
//        ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//        // точечный источник света 1
//        ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//        ourShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[0].constant", 1.0f);
//        ourShader.setFloat("pointLights[0].linear", 0.09);
//        ourShader.setFloat("pointLights[0].quadratic", 0.032);
//        // точечный источник света 2
//        ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//        ourShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[1].constant", 1.0f);
//        ourShader.setFloat("pointLights[1].linear", 0.09);
//        ourShader.setFloat("pointLights[1].quadratic", 0.032);
//        // точечный источник света 3
//        ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//        ourShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[2].constant", 1.0f);
//        ourShader.setFloat("pointLights[2].linear", 0.09);
//        ourShader.setFloat("pointLights[2].quadratic", 0.032);
//        // точечный источник света 4
//        ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//        ourShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[3].constant", 1.0f);
//        ourShader.setFloat("pointLights[3].linear", 0.09);
//        ourShader.setFloat("pointLights[3].quadratic", 0.032);
//        // прожектор
//        ourShader.setVec3("spotLight.position", camera.Position);
//        ourShader.setVec3("spotLight.direction", camera.Front);
//        ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//        ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//        ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("spotLight.constant", 1.0f);
//        ourShader.setFloat("spotLight.linear", 0.09);
//        ourShader.setFloat("spotLight.quadratic", 0.032);
//        ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // преобразования Вида/Проекции
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

//        // мировое преобразование
//        glm::mat4 model = glm::mat4(1.0f);
//        ourShader.setMat4("model", model);

        // рендеринг загруженной модели
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // смещаем вниз чтобы быть в центре сцены
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// объект слишком большой для нашей сцены, поэтому немного уменьшим его
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader, camera);

//        // Связывание текстуры (диффузной карты)
//        glActiveTexture(GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, texture1);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//        glActiveTexture(GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D, texture1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);

        // Рендеринг ящика
//        ourShader.use();
//        glBindVertexArray(VAO);
//
//        for(unsigned int i = 0; i < 10; i++)
//        {
//            // вычисляем матриц модели для каждого объекта и передаём её в шейдер
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * (i + 1);
//            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }

        // также отрисовываем наш объект-"лампочку"
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);

        // а теперь мы отрисовывает столько ламп, сколько у нас есть точечных источников света
        glBindVertexArray(lightVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // меньший куб
            lampShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий Ввода/Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Опционально: освобождаем все ресурсы, как только они выполнили своё предназначение
//    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();

    return 0;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

int moveInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        return 1;
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        return 2;
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        return 3;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        return 4;
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