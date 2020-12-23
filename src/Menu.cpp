//
// Created by moroz on 06.12.2020.
//

#include "Menu.h"

std::vector<float> vertices{
        // координаты          // цвета           // текстурные координаты
        0.6f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
        0.6f, 0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
        -0.6, 0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
        -0.6f,  0.6f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
};

std::vector<float> vertices2 = {
        // координаты          // цвета           // текстурные координаты
        0.6f,  -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
        0.6f, -0.6f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
        -0.6, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
        -0.6f,  -0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
};

Menu::Menu(GLFWwindow *window, const unsigned int &SCR_HEIGHT, const unsigned int &SCR_WIDTH):
        button_start("textures/start_text.png", "textures/start_text_act.png", vertices),
        button_map_editor("textures/map_editor_text.png", "textures/map_editor_text_act.png", vertices2),
        window(window),
        map_editor_handler(nullptr),
        SCR_WIDTH(SCR_WIDTH), SCR_HEIGHT(SCR_HEIGHT){
    button_start.activate();
    draw = std::bind(&Menu::draw_menu, this);
    processInput = std::bind(&Menu::process_input, this);
}

void Menu::process_input(){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        Map_editor_handler map_editor();
        //draw = std::bind(&Map_editor_handler::draw, &map_editor);
    }

    if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ||
       (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)){
        if (!button_start.is_active()) {
            button_start.activate();
            button_map_editor.deactivate();
        }
    }

    if((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ||
       (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)) {
        if (button_start.is_active()) {
            button_start.deactivate();
            button_map_editor.activate();
        }
    }
//
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
        if (button_start.is_active()) {
            //start game
        } else {
            map_editor_handler = std::make_shared<Map_editor_handler>(window, SCR_HEIGHT, SCR_WIDTH);
            draw = std::bind(&Map_editor_handler::draw, map_editor_handler);
            processInput = std::bind(&Map_editor_handler::processInput, map_editor_handler);
        }
    }

}

void Menu::draw_menu() {
    Shader shader("shader.vs", "shader.fs");
    shader.use();
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int VBO[2], VAO[2], EBO[2];
    glGenVertexArrays(2, VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glGenBuffers(1, &EBO[0]);
    //draw_triangle(VAO, VBO, EBO);
    button_start.draw(VAO[0], VBO[0], EBO[0]);
    button_map_editor.draw(VAO[1], VBO[1], EBO[1]);
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
}
