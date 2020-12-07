//
// Created by moroz on 05.12.2020.
//

/*
 *
 *
 */
#include "Interface.h"

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
)";
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
)";

float i = 0.0f;
void draw_button(unsigned int &VBO, unsigned int &VAO, unsigned int &EBO){


};

void draw_triangle(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){


    // задание вершин (и буфера(ов)) и настройка вершинных атрибутов
    // ------------------------------------------------------------------
    float vertices[] = {
            // координаты          // цвета           // текстурные координаты
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // верхняя правая вершина
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // нижняя левая вершина
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // верхняя левая вершина
    };
    unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // цветовые атрибуты
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // атрибуты текстурных координат
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // загрузка и создание текстуры
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // загрузка изображения, создание текстуры и генерирование mipmap-уровней
    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
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

    glBindTexture(GL_TEXTURE_2D, texture);

    // Рендеринг ящика
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
void Interface::start_draw() {
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
            // координаты          // цвета           // текстурные координаты
            0.6f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
            0.6f, 0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
            -0.6, 0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
            -0.6f,  0.6f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
    };

    float vertices2[] = {
            // координаты          // цвета           // текстурные координаты
            0.6f,  -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
            0.6f, -0.6f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
            -0.6, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
            -0.6f,  -0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
    };

    unsigned int VBO[2], VAO[2], EBO[2];
    glGenVertexArrays(2, VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glGenBuffers(1, &EBO[0]);
    //draw_triangle(VAO, VBO, EBO);
    button_start.draw(vertices, VAO[0], VBO[0], EBO[0]);
    button_map_editor.draw(vertices2, VAO[1], VBO[1], EBO[1]);
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);


}

void Interface::cycle() {


    // Цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput();

        // Рендеринг
        glUseProgram(shaderProgram);


        draw();



        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий Ввода\Вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Опционально: освобождаем все ресурсы, как только они выполнили своё предназначение


    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий
void Interface::processInput(){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){

        Map_editor_handler map_editor;
        i+=0.01f;
        //draw = std::bind(&Map_editor_handler::draw, &map_editor);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (!button_start.is_activated()) {
            button_start.activate();
            button_map_editor.deactivate();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (button_start.is_activated()) {
            button_start.deactivate();
            button_map_editor.activate();
        }
    }

}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или оперионной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // Убеждаемся, что окно просмотра соответствует новым размерам окна
    // Обратите внимание, что ширина и высота будут значительно больше, чем указано на Retina-дисплеях
    glViewport(0, 0, width, height);
}

Interface::~Interface() {

}

Interface::Interface(): button_start("textures/button8.jpg", "textures/button8_act.jpg"),
button_map_editor("textures/button9.jpg", "textures/button9_act.jpg"){

    button_start.activate();
    // glfw: инициализация и конфигурирование
    draw = std::bind(&Interface::start_draw, this);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: создание окна
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FigureQuiz", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }



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
    shaderProgram = glCreateProgram();
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

}


