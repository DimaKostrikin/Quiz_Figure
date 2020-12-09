#include "Map_editor_handler.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 1024;

Map_editor_handler::Map_editor_handler() {
    cur_container = 0;
    scene_init();
    toolbar_init();
    window = nullptr;
    n = 0;
}

Map_editor_handler::Map_editor_handler(GLFWwindow *window) {
    n = 0;
    cur_container = 0;
    this->window = window;
    scene_init();
    cur_elem=0;
    scene = std::make_shared<Scene>();
    //label = std::make_shared<Parameters_label>();
    std::vector<float> vertices_button {
            // координаты

            -0.75f,  0.95f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.75f, 0.75f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, 0.75f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 0.95f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };

    std::vector<float> vertices_button2 {
            // координаты
            -0.75f,  0.65f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.75f, 0.45f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, 0.45f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 0.65f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    std::vector<float> vertices_button3 {
            // координаты
            -0.75f,  0.35f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.75f, 0.15f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, 0.15f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 0.35f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    std::vector<float> vertices_button4 {
            // координаты
            -0.75f,  0.05f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.75f, -0.15f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, -0.15f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 0.05f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };

    std::vector<float> vertices_button5 {
            // координаты
            -0.65f,  -0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.65f, -0.35f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, -0.35f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, -0.25f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    std::vector<float> vertices_button6 {
            // координаты
            -0.65f,  -0.55f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.65f, -0.65f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, -0.65f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, -0.55f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };


    toolbar_buttons.emplace_back("textures/start_icon.jpg", "textures/start_icon_act.jpg", vertices_button, START);
    toolbar_buttons.emplace_back("textures/exit_icon.jpg", "textures/exit_icon_act.jpg", vertices_button2, FINISH);
    toolbar_buttons.emplace_back("textures/cube_hole_icon.jpg", "textures/cube_hole_icon_act.jpg", vertices_button3, HOLE);
    toolbar_buttons.emplace_back("textures/cube_icon.jpg", "textures/cube_icon_act.jpg", vertices_button4, CUBE);
    toolbar_buttons.emplace_back("textures/connect_text.jpg", "textures/connect_text_act.jpg", vertices_button5, CONNECT);
    toolbar_buttons.emplace_back("textures/finish_text.jpg", "textures/finish_text_act.jpg", vertices_button6, SAVE);

    toolbar_buttons[cur_elem].activate();
}

void Map_editor_handler::scene_init() {
    //создание сцены
}

void Map_editor_handler::toolbar_init() {
    glClearColor(0.51f, 0.73f, 0.73f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
            // координаты

            0.7f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.5, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.5f, 0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };


    unsigned int indices[] = {  // помните, что мы начинаем с 0!
            0, 1, 3,   // первый треугольник
            1, 2, 3    // второй треугольник
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);



// Шаг №1: Копируем наш массив вершин в вершинный буфер
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// Шаг №2: Копируем наш индексный массив в элементный буфер
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// Шаг №3: Устанавливаем указатели вершинных атрибутов
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //создание тулбара с инструментами
}

void Map_editor_handler::on_key_click() {
    /*//перемещение элемента по полю по сетке
    std::shared_ptr<Object> obj;
    //доп параметром добавить кнопку
    //стирает объект
    scene->clear_object(obj);
    map->change_object( obj);
    //перерисовывает элемент
    scene->change_object(obj);*/
}

Map_editor_handler::~Map_editor_handler() {

}

void Map_editor_handler::draw() {
    Shader shader("shader.vs", "shader.fs");
    shader.use();
    toolbar_init();
    scene->draw();


    for(auto &i: toolbar_buttons)
    {
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        i.draw(VAO, VBO, EBO);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    if (!scene->container.empty()){
        if (scene->container[scene->cur_elem].is_activated()) {
            double x1 = (scene->container[scene->cur_elem].vertices[16] + 1.0f) * (SCR_WIDTH / 2);
            double x2 = (scene->container[scene->cur_elem].vertices[0] + 1.0f) * (SCR_WIDTH / 2);
            double y1 = (1.0f - scene->container[scene->cur_elem].vertices[1]) * (SCR_HEIGHT / 2);
            double y2 = (1.0f - scene->container[scene->cur_elem].vertices[9]) * (SCR_HEIGHT / 2);
            // осторожно !1!!1
            double x = abs(x2 - x1);
            //label->x = x1+(x2 - x1)/2;
            //label->y = y1+(y2 - y1)/2;
        } //else label->clear();
    }
    //label->draw();

}

double get_d(float f){
    double d;
    if (f <= 0){
        f += 1.0f;
    } else {
        f -= 1.0f;
    }
    d = f * (SCR_WIDTH / 2);
    return d;
}




void Map_editor_handler::processInput() {

    double x, y;

    glfwGetCursorPos(window, &x, &y);
    int j = 0;
    if (!scene->connection_mode) {
        for (auto &i: toolbar_buttons) {
            double x1 = (i.vertices[16] + 1.0f) * (SCR_WIDTH / 2);
            double x2 = (i.vertices[0] + 1.0f) * (SCR_WIDTH / 2);
            double y1 = (1.0f - i.vertices[1]) * (SCR_HEIGHT / 2);
            double y2 = (1.0f - i.vertices[9]) * (SCR_HEIGHT / 2);
            i.deactivate();
            if ((x1 < x) && (x < x2)
                && (y1 < y) && (y < y2)) {
                cur_elem = j;
                i.activate();
            }
            ++j;
        }
    }
    //GLFW_MOUSE_BUTTON_LEFT
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        std::vector<float> vertices_button{
                // координаты

                0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // верхняя правая
                0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // нижняя правая
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // нижняя левая
                0.0f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f

        };
        if (toolbar_buttons[cur_elem].is_activated()) {
            switch (toolbar_buttons[cur_elem].type) {
                case START: {
                    scene->container.emplace_back(Map_object
                    ("textures/start.jpg", "textures/start_act.jpg", vertices_button,
                                                                  START, ++scene->id));
                    break;
                }
                case FINISH: {
                    scene->container.emplace_back(Map_object
                    ("textures/exit.jpg", "textures/exit_act.jpg", vertices_button,
                                                                  FINISH, ++scene->id));
                }
                    break;
                case HOLE: {
                    scene->container.emplace_back(Map_object
                    ("textures/cube_hole.jpg", "textures/cube_hole_act.jpg", vertices_button,
                                                               HOLE, ++scene->id));
                }
                    break;
                case CUBE: {
                    scene->container.emplace_back(Map_object
                    ("textures/blue.jpg", "textures/dark_blue.jpg", vertices_button,
                                                               CUBE, ++scene->id));
                }
                    break;
                case CONNECT: {
                    if (scene->container.size() >= 2)
                        scene->connection_mode=true;

                }
                    break;
                default:
                    break;
            };
        }
        j = 0;
        bool is_not_activated=true;
        if (!scene->connection_mode) {
            for (auto &i: scene->container) {
                i.deactivate();
                double x1 = (i.vertices[16] + 1.0f) * (SCR_WIDTH / 2);
                double x2 = (i.vertices[0] + 1.0f) * (SCR_WIDTH / 2);
                double y1 = (1.0f - i.vertices[1]) * (SCR_HEIGHT / 2);
                double y2 = (1.0f - i.vertices[9]) * (SCR_HEIGHT / 2);
                if (is_not_activated) {
                    if ((x1 < x) && (x < x2)
                        && (y1 < y) && (y < y2)) {
                        scene->cur_elem = j;
                        i.activate();
                        is_not_activated = false;
                    }
                    ++j;
                }
            }
        } else{
            if (!scene->container.empty())
                scene->container[scene->cur_elem].deactivate();
            j=0;
            for (auto &i: scene->container) {
                double x1 = (i.vertices[16] + 1.0f) * (SCR_WIDTH / 2);
                double x2 = (i.vertices[0] + 1.0f) * (SCR_WIDTH / 2);
                double y1 = (1.0f - i.vertices[1]) * (SCR_HEIGHT / 2);
                double y2 = (1.0f - i.vertices[9]) * (SCR_HEIGHT / 2);
                if (n < 2) {
                    if ((x1 < x) && (x < x2)
                        && (y1 < y) && (y < y2)) {
                        i.activate();
                        n++;
                        if (n <= 1) save = j;
                        else {
                            connect(save, j);
                            scene->container[save].deactivate();
                            scene->container[j].deactivate();
                            scene->connection_mode=false;
                            n = 0;
                        }
                    }
                }
                ++j;
                }
        }

    }

//

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_activated())
                scene->container[scene->cur_elem].up();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_activated())
                scene->container[scene->cur_elem].down();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_activated())
                scene->container[scene->cur_elem].left();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_activated())
                scene->container[scene->cur_elem].right();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) {
        if (cur_container==1){
            scene->container.erase(scene->container.begin()+scene->cur_elem)[scene->cur_elem];
            std::vector<Map_object> new_container;
            for (auto &i: scene->container){
                new_container.push_back(i);
            }
            scene->container=std::move(new_container);
            new_container.clear();
        }
    }

}

std::shared_ptr<Container_map> Map_editor_handler::create_map() {
    std::shared_ptr<Container_map>(scene);
    return std::shared_ptr<Container_map>();
}


void Map_editor_handler::connect(size_t i, size_t j) {
    if (scene->container[i].is_activator()){
        if (scene->container[j].is_activated())
            scene->container[j].connect = scene->container[i].id; // финиш открывается из-за дырки
        if (scene->container[j].is_dynamic())
            scene->container[i].connect = scene->container[j].id; // дырка открывается из-за куба
    } else if (scene->container[i].is_activated()){
        if (scene->container[j].is_activator())
            scene->container[i].connect = scene->container[j].id; // финиш открывается из-за дырки
    } else if (scene->container[i].is_dynamic()){
        if (scene->container[j].is_activator())
            scene->container[j].connect = scene->container[i].id; // финиш открывается из-за дырки
    }
}

