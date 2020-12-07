#include <iostream>

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int moveInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// // Для прямоугольника
//const char* vertexShaderSource = "#version 330 core\n"
//                                 "layout (location = 0) in vec3 aPos;\n"
//                                 "uniform vec2 coord_delta;\n"
//                                 "void main()\n"
//                                 "{\n"
//                                 "   gl_Position = vec4(aPos.x + coord_delta.x, aPos.y + coord_delta.y, aPos.z, 1.0);\n"
//                                 "}\0";

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"  // позиция атрибута, содержащего переменные координат, устанавливается в 0
                                 "layout (location = 1) in vec3 aColor;\n"  // позиция атрибута, содержащего переменные цвета, устанавливается в 1
                                 "  \n"
                                 "out vec3 ourColor;\n"  // на выходе – значение цвета, передаваемое во фрагментный шейдер
                                 " \n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos, 1.0);\n"
                                 "    ourColor = aColor;\n"  // присваиваем переменной ourColor значение цвета, которое мы получили из данных вершины
                                 "}";

//const char* fragmentShaderSource = "#version 330 core\n"
//                                   "out vec4 FragColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                   "}\n\0";

// // Для прямоугольника
//const char* fragmentShaderSource = "#version 330 core\n"
//                                   "out vec4 FragColor;\n"
//                                   "  \n"
//                                   "uniform vec4 ourColor;"
//                                   " \n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "    FragColor = ourColor;\n"
//                                   "} ";


const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;  \n"
                                   "in vec3 ourColor;\n"
                                   "  \n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(ourColor, 1.0);\n"
                                   "}";

int main() {
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

    // Вершинный шейдер
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Проверка на наличие ошибок компилирования вершинного шейдера
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Фрагментный шейдер
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Проверка на наличие ошибок компилирования фрагментного шейдера
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Связывание шейдеров
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Проверка на наличие ошибок компилирования связывания шейдеров
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Указывание вершин (и буферов) и настройка вершинных атрибутов

//    // Вершины для прямоугольника
//    float vertices[] = {
//            0.5f,  0.5f, 0.0f,  // верхняя правая
//            0.5f, -0.5f, 0.0f,  // нижняя правая
//            -0.5f, -0.5f, 0.0f,  // нижняя левая
//            -0.5f,  0.5f, 0.0f   // верхняя левая
//    };

    float vertices[] = {
            // координаты         // цвета
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // нижняя правая вершина
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // нижняя левая вершина
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // верхняя вершина
    };

//    unsigned int indices[] = {  // помните, что мы начинаем с 0!
//            0, 1, 3,   // первый треугольник
//            1, 2, 3    // второй треугольник
//    };

    unsigned int VBO, VAO;
//    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    // Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
    // Шаг №0: Связывание объекта вершинного массива
    glBindVertexArray(VAO);

    // Шаг №1: Копируем наш массив вершин в вершинный буфер
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    // Шаг №2: Копируем наш индексный массив в элементный буфер
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Шаг №3: Устанавливаем указатели вершинных атрибутов
    // Координатный атрибут
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Цветовой атрибут
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);

    // Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал
    // VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно
    // выполнить отвязку
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Вы можете отменить привязку VАО после этого, чтобы другие вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается)
    // Модификация других VAO требует вызов glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
    glBindVertexArray(0);

//    // Поскольку у нас есть только один шейдер, мы также можем просто активировать наш шейдер заранее, если нужно
//    glUseProgram(shaderProgram);


    // Раскомментируйте строчку ниже для отрисовки полигонов в режиме каркаса
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Цикл рендеринга

//    // Для движения прямоугольника
//    float x_delta = 0;
//    float y_delta = 0;
    while(!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);
//        moveInput(window);
//        switch (moveInput(window)) {
//            case 1:
//                y_delta += 0.1f;
//                break;
//            case 2:
//                y_delta -= 0.1f;
//                break;
//            case 3:
//                x_delta -= 0.1f;
//                break;
//            case 4:
//                x_delta += 0.1f;
//                break;
//            default:
//                break;
//        }

        // Выполнение рендеринга
        //Очищаем цветовой буфер
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Убеждаемся, что активировали шейдер
        glUseProgram(shaderProgram);

//        // Для движения прямоугольника
//        // Обновляем для uniform-переменной значение color
//        float timeValue = glfwGetTime();
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        float redValue = sin(2 * timeValue) / 2.0f + 0.5f;
//        float blueValue = sin(3 * timeValue) / 2.0f + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
//
//        // Обновляем положение прямоугольника
//        int vertexCoordDelta = glGetUniformLocation(shaderProgram, "coord_delta");
//        glUniform2f(vertexCoordDelta, x_delta, y_delta);

        // Отрисовка
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз (но мы сделаем это, чтобы всё было немного организованнее)
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // не нужно каждый раз его отвязывать

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий Ввода/Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Опционально: освобождаем все ресурсы, как только они выполнили своё предназначение
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();

    return 0;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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