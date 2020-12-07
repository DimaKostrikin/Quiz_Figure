//
// Created by moroz on 06.12.2020.
//

#include "Menu.h"

Menu::Menu(GLFWwindow *window): button_start("textures/button8.jpg", "textures/button8_act.png"),
        button_map_editor("textures/button9.jpg", "textures/button9_act.jpg"), window(window) {
    button_start.activate();
    draw = std::bind(&Menu::draw_menu, this);
    processInput = std::bind(&Menu::process_input, this);
}

void Menu::process_input(){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        Map_editor_handler map_editor;
        //draw = std::bind(&Map_editor_handler::draw, &map_editor);
    }

    if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ||
       (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)){
        if (!button_start.is_activated()) {
            button_start.activate();
            button_map_editor.deactivate();
        }
    }

    if((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ||
       (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)) {
        if (button_start.is_activated()) {
            button_start.deactivate();
            button_map_editor.activate();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
        if (button_start.is_activated()) {
            //start game
        } else {
            map_editor_handler = std::make_shared<Map_editor_handler>();
            draw = std::bind(&Map_editor_handler::draw, map_editor_handler);
        }
    }

}

void Menu::draw_menu() {
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

template<std::size_t N>
void Button_entry<N>::activate(){
    set_texture(texture_active);
    activated = true;
}

template<std::size_t N>
void Button_entry<N>::deactivate(){
    set_texture(texture_passive);
    activated = false;
}

template<std::size_t N>
void Button_entry<N>::draw(float (&vertices)[N], unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
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

    glBindTexture(GL_TEXTURE_2D, texture_cur);


    // Рендеринг ящика
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

template<std::size_t N>
void Button_entry<N>::set_texture(unsigned int texture){
    texture_cur = texture;
}