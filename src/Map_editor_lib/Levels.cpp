#include "Map_editor_lib/Levels.h"
#include "Features_lib/Logic_manager.h"

const float coord = 0.2f;
const int num_of_levels = 5;
bool state = false;



std::vector<float> vertices_levels {
        // координаты          // цвета           // текстурные координаты
        -0.5f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f,  1.0f, // верхняя правая вершина
        -0.5f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
        -0.7f,  0.1f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0, 0.0f, // нижняя левая вершина
        -0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,  1.0f  // верхняя левая вершина
};

std::vector<float> vertices_offset {
    0.1f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.1f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.1f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.1f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f
};

Levels::Levels(GLFWwindow *window) : num_of_level(1), window(window) {
    std::string path_to_img = "textures/lvl";
    std::string path_ending = ".png";
    std::string act_path_ending = "_act.png";
    std::vector<float> vertices_l = vertices_levels;
    std::vector<float> current_offset(32);
    for (int i = 0; i < num_of_levels; ++i) {
        if (i) {
            for (int o = 0; o < vertices_offset.size(); ++o) {
                current_offset[o] = vertices_offset[o] * 3 * i;
            }
            for (int j = 0; j < vertices_offset.size(); ++j) {
                vertices_l[j] = (vertices_levels[j] + current_offset[j]);
            }
        }


        buttons_levels.emplace_back(Button_entry(path_to_img + std::to_string(i+1) + path_ending,
                                 path_to_img + std::to_string(i+1) + act_path_ending, vertices_l));
    }
    buttons_levels.begin()->activate();
    draw = std::bind(&Levels::draw_levels, this);
    processInput = std::bind(&Levels::process_input, this);

    it_lvl = buttons_levels.begin();
}


int Levels::process_input() {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (Key_press(GLFW_KEY_D, window, state_keys.State_D)) {
        it_lvl->deactivate();
        ++it_lvl;
        it_lvl->activate();
        ++num_of_level;

        if (it_lvl == buttons_levels.end()) {  // Если кнопка последняя, то мы возвращаемся к первой.
            it_lvl->deactivate();
            it_lvl = buttons_levels.begin();
            it_lvl->activate();
            num_of_level = 1;
        }

    }

    if (Key_press(GLFW_KEY_A, window, state_keys.State_A)) {
        if (it_lvl == buttons_levels.begin()) {
            it_lvl->deactivate();
            it_lvl = buttons_levels.end();
            it_lvl--;
            it_lvl->activate();
            num_of_level = num_of_levels;
        } else {
            it_lvl->deactivate();
            --it_lvl;
            it_lvl->activate();
            --num_of_level;
        }


    }
//
    if (Key_press(GLFW_KEY_E, window, state_keys.State_E)){
        std::cout << num_of_level << std::endl;
        return num_of_level;
    }
    return NOTHING;
}


void Levels::draw_levels() {
    Shader shader("include/Map_editor_lib/shader.vs", "include/Map_editor_lib/shader.fs");
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
    //button_start.draw(VAO[0], VBO[0], EBO[0]);
    for (auto it = buttons_levels.begin(); it != buttons_levels.end(); ++it) {
        it->draw(VAO[0], VBO[0], EBO[0]);
    }
    //button_map_editor.draw(VAO[1], VBO[1], EBO[1]);
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
}
