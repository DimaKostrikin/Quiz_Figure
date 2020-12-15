#include <iostream>

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "My_camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int moveInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"  // позиция атрибута, содержащего переменные координат, устанавливается в 0
                                 "layout (location = 1) in vec3 aColor;\n"  // позиция атрибута, содержащего переменные цвета, устанавливается в 1
                                 "  \n"
                                 "out vec3 ourColor;\n"  // на выходе – значение цвета, передаваемое во фрагментный шейдер
//                                 "uniform mat4 transform;\n"
                                 "void main()\n"
                                 "{\n"
//                                 "    gl_Position = transform * vec4(aPos, 1.0);\n"
                                 "    gl_Position = vec4(aPos, 1.0);\n"
                                 "    ourColor = aColor;\n"  // присваиваем переменной ourColor значение цвета, которое мы получили из данных вершины
                                 "}";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;  \n"
                                   "in vec3 ourColor;\n"
                                   "  \n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(ourColor, 1.0);\n"
                                   "}";

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float deltaTime = 0.0f;	// время между текущим и последним кадрами
float lastFrame = 0.0f; // время последнего кадра

//для мышки
//float yaw = -90.f;
//float pitch = 0.f;
bool firstMouse = true;
//float fov = 45;

//для камеры
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

//положение источника света
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {
    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My awesome window!!!", NULL, NULL);
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
    // Компилирование нашей шейдерной программы
    Shader ourShader("../Shader_files/shader.vs", "../Shader_files/shader.fs");
    Shader lampShader("../Shader_files/lampShader.vs", "../Shader_files/lampShader.fs");

    //координаты вершин и координаты текстур
//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };

//координат вершин и нормали к ним(захардкожены для статического куба)
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // Мировые координаты наших кубиков
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
    };

    unsigned int VBO, VAO, EBO, lightVAO;

    // 1. настраиваем VAO (и VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //2. настраиваем VAO света (VBO остается неизменным; вершины те же и для светового объекта, который также является 3D-кубом)
    glGenVertexArrays(1, &lightVAO);

    //объект освещения
    glBindVertexArray(lightVAO);

    //нам нужно только привязаться к VBO (чтобы связать его с glVertexAttribPointer), не нужно заполнять его; данные VBO уже содержат все, что нам нужно(они уже привязаны, но мы делаем это снова в образовательных целях)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

//    // Нам нужно только привязаться к VBO. VBO контейнера уже содержат нужные данные
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);

//    // Устанавливаем атрибуты вершин (только данные о местоположении для нашей лампы)
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
//    // Шаг №0: Связывание объекта вершинного массива
//    glBindVertexArray(VAO);
//
//    // Шаг №1: Копируем наш массив вершин в вершинный буфер
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // Шаг №2: Копируем наш индексный массив в элементный буфер
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // Шаг №3: Устанавливаем указатели вершинных атрибутов
//    // координатные атрибуты
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // атрибуты текстурных координат
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    // загрузка и создание текстуры
    // -------------------------
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // загрузка изображения, создание текстуры и генерирование mipmap-уровней
    int width, height, nrChannels;
    //первая текстура
    unsigned char* data = stbi_load("../textures/wooden_box.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    //вторая текстура
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // загрузка изображения, создание текстуры и генерирование mipmap-уровней
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../textures/smile.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // файл smile.png имеет альфа-канал(прозрачность), поэтому необходимо использовать пераметр GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);


    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    ourShader.use();
//    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // устанавливаем вручную…
    ourShader.setInt("texture2", 1); // …или с помощью шейдерного класса

    ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    ourShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    ourShader.setVec3("lightPos", lightPos);
    ourShader.setVec3("viewPos", camera.Position);

    //включаем Z-буфер
    glEnable(GL_DEPTH_TEST);

    //камера
//    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    //матрица вида
    glm::mat4 view;

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Убеждаемся, что активировали шейдер
//        glUseProgram(shaderProgram);

        // убеждаемся, что активировали шейдер прежде, чем настраивать uniform-переменные/объекты_рисования
        ourShader.use();
        ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        // Связывание текстуры
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

//        // создаем преобразование
//        glm::mat4 trans = glm::mat4(1.0f);
//        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        //матрица модели
        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));


        //матрица вида
//        glm::mat4 view = glm::mat4(1.0f);
//        const float radius = 10.0f;
//        float camX = sin(glfwGetTime()) * radius;
//        float camZ = cos(glfwGetTime()) * radius;
//        glm::mat4 view;
//        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0,0.0));
//        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //мы перемещаем сцену в направлении, обратном направлению предполагаемого движения
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        //матрица проекции
        glm::mat4 projection;
//        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);


        // получаем location uniform-переменной матрицы и настраиваем её
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//        ourShader.setMat4("projection", projection);


        // Рендеринг ящика
        ourShader.use();
        glBindVertexArray(VAO);

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i + 1);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // также отрисовываем наш объект-"лампочку"
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // куб, меньшего размера
        lampShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Отрисовка
//        glUseProgram(shaderProgram);
//        ourShader.use();
//        glBindVertexArray(VAO); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз (но мы сделаем это, чтобы всё было немного организованнее)
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // не нужно каждый раз его отвязывать

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий Ввода/Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Опционально: освобождаем все ресурсы, как только они выполнили своё предназначение
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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