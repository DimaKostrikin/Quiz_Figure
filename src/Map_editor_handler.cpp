#include "Map_editor_handler.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 1024;

Map_editor_handler::Map_editor_handler() {
    cur_container = 0;
    scene_init();
    toolbar_init();
    window = nullptr;
}

Map_editor_handler::Map_editor_handler(GLFWwindow *window) {

    cur_container = 0;
    this->window = window;
    scene_init();
    cur_elem=0;
    scene = std::make_shared<Scene>();
    label = std::make_shared<Parameters_label>();
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
            -0.65f,  0.35f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.65f, 0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, 0.25f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 0.35f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    std::vector<float> vertices_button4 {
            // координаты
            -0.65f,  0.15f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.65f, 0.05f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, 0.05f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 0.15f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };

    toolbar_buttons.emplace_back("textures/start_icon.jpg", "textures/start_icon_act.jpg", vertices_button, START);
    toolbar_buttons.emplace_back("textures/exit_icon.jpg", "textures/exit_icon_act.jpg", vertices_button2, FINISH);
    toolbar_buttons.emplace_back("textures/connect_text.jpg", "textures/connect_text_act.jpg", vertices_button3, CONNECT);
    toolbar_buttons.emplace_back("textures/finish_text.jpg", "textures/finish_text_act.jpg", vertices_button4, SAVE);

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
    label->draw();
    shader.use();

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
    //GLFW_MOUSE_BUTTON_LEFT
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        std::vector<float> vertices_button3{
                // координаты

                0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // верхняя правая
                0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // нижняя правая
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // нижняя левая
                0.0f, 0.2f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f

        };
        if (toolbar_buttons[cur_elem].is_activated()) {
            switch (toolbar_buttons[cur_elem].type) {
                case START: {
                    Map_object elem("textures/start.jpg", "textures/start_act.jpg", vertices_button3,
                                        START);
                    scene->container.push_back(elem);
                    break;
                }
                case FINISH: {
                    Map_object elem("textures/exit.jpg", "textures/exit_act.jpg", vertices_button3,
                                        FINISH);
                    scene->container.push_back(elem);
                }
                    break;
                default:
                    break;
            };
        }
        j = 0;
        bool is_not_activated=true;
        for (auto &i: scene->container) {
            i.deactivate();
            double x1 = (i.vertices[16] + 1.0f) * (SCR_WIDTH / 2);
            double x2 = (i.vertices[0] + 1.0f) * (SCR_WIDTH / 2);
            double y1 = (1.0f - i.vertices[1]) * (SCR_HEIGHT / 2);
            double y2 = (1.0f - i.vertices[9]) * (SCR_HEIGHT / 2);
            if (is_not_activated){
                if ((x1 < x) && (x < x2)
                    && (y1 < y) && (y < y2)) {
                    scene->cur_elem = j;
                    i.activate();
                    is_not_activated=false;
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
