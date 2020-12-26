//
// Created by moroz on 06.12.2020.
//

#include "Map_editor_lib/Menu.h"
#include "Features_lib/Logic_manager.h"

/* эт кжтс не нужно
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
*/
std::vector<float> vertices{
        // координаты          // цвета           // текстурные координаты
        0.6f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
        0.6f,  0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
        -0.6,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
        -0.6f, 0.6f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
};

std::vector<float> vertices2 = {
        // координаты          // цвета           // текстурные координаты
        0.6f,  -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
        0.6f, -0.6f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
        -0.6, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
        -0.6f,  -0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
};

Menu::Menu(GLFWwindow *window): button_start("textures/start_text.png", "textures/start_text_act.png", vertices),
        button_map_editor("textures/map_editor_text.png", "textures/map_editor_text_act.png", vertices2), window(window),
        map_editor_handler(nullptr), shader("include/Map_editor_lib/shader.vs", "include/Map_editor_lib/shader.fs"){
    button_start.activate();
    draw = std::bind(&Menu::draw_menu, this);
    processInput = std::bind(&Menu::process_input, this);
}


int Menu::process_input(){


    if(Key_press(GLFW_KEY_Q, window, state_keys.State_Q)){
        return EXIT;
    }

    if(Key_press(GLFW_KEY_W, window, state_keys.State_W)){
        if (!button_start.is_active()) {
            button_start.activate();
            button_map_editor.deactivate();
        }
    }

    if(Key_press(GLFW_KEY_S, window, state_keys.State_S)) {
        if (button_start.is_active()) {
            button_start.deactivate();
            button_map_editor.activate();
        }
    }
//
    if (Key_press(GLFW_KEY_E, window, state_keys.State_A)){
        if (button_start.is_active()) {
            return START_GAME;
        } else {
            return REDACTOR;
        }
    }
    return NOTHING;

}

void Menu::draw_menu() {
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
