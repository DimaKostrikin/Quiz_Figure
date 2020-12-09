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



    Button_toolbar<32> button("textures/start_icon.jpg", "textures/start_icon_act.jpg", vertices_button, START);

    Button_toolbar<32> button2("textures/exit_icon.jpg", "textures/exit_icon_act.jpg", vertices_button2, FINISH);

    Button_toolbar<32> button3("textures/finish_text.jpg", "textures/finish_text_act.jpg", vertices_button3, SAVE);


    toolbar_buttons.push_back(button);
    toolbar_buttons.push_back(button2);
    toolbar_buttons.push_back(button3);

    toolbar_buttons[cur_elem].activate();
}

void Map_editor_handler::on_mouse_click() {
    //нажатие на объект
/*
    //если объект существующий
    //тут еще айди объекта передает
    scene->init_label();

    //нажатие на тулбар элемент
    //по кейсу создаем элемент
    std::shared_ptr<Object> obj;
    map->add_object(obj);
    scene->draw_object(obj);

    //нажатие на label
    //принимает новое состояние
    scene->label->changed();

    //нажатие save
    parser.create_json(map);*/



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

    glfwGetCursorPos ( window, &x, &y );
    int j = 0;
    for (auto &i: toolbar_buttons){
        double x1 = (i.vertices[16]+1.0f) * (SCR_WIDTH / 2);
        double x2 = (i.vertices[0]+1.0f) * (SCR_WIDTH / 2);
        double y1 = (1.0f-i.vertices[1]) * (SCR_HEIGHT / 2);
        double y2 = (1.0f-i.vertices[9]) * (SCR_HEIGHT / 2);
        if ((x1 < x) && (x<x2)
                && (y1 < y) && (y<y2)){
                double z = (i.vertices[16] + 1.0f) * (SCR_WIDTH / 2);
                toolbar_buttons[cur_elem].deactivate();
                cur_elem = j;
                i.activate();
                ++j;
        } else { i.deactivate();}
    }
    //GLFW_MOUSE_BUTTON_LEFT
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        if (cur_container==0){
            if (cur_elem != 0){
                toolbar_buttons[cur_elem].deactivate();
                --cur_elem;
                toolbar_buttons[cur_elem].activate();
            }
        } else {
            if (scene->cur_elem != 0){
                scene->container[scene->cur_elem].deactivate();
                --scene->cur_elem;
                scene->container[scene->cur_elem].activate();
            }
        }

    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (cur_container==0){
            if (cur_elem < toolbar_buttons.size()-1){
                    toolbar_buttons[cur_elem].deactivate();
                    ++cur_elem;
                    toolbar_buttons[cur_elem].activate();
                }
        } else {
            if (scene->cur_elem < scene->container.size()-1){
                scene->container[scene->cur_elem].deactivate();
                ++scene->cur_elem;
                scene->container[scene->cur_elem].activate();
            }
        }
    }
//
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
        std::vector<float> vertices_button3 {
                // координаты

                0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
                0.2f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
                0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
                0.0f, 0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

        };
        switch ( toolbar_buttons[cur_elem].type ) {
            case START:{
                Map_object<32> elem("textures/start_icon.jpg", "textures/start_icon_act.jpg", vertices_button3, START);
                scene->container.push_back(elem);
                break;}
            case FINISH:{
                Map_object<32> elem("textures/exit_icon.jpg", "textures/exit_icon_act.jpg", vertices_button3, FINISH);
                scene->container.push_back(elem);}
                break;
            default:
                break;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if ((cur_container==0) && (!scene->container.empty())){
            cur_container=1;
            toolbar_buttons[cur_elem].deactivate();
            scene->container[scene->cur_elem].activate();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (cur_container==1){
            cur_container=0;
            toolbar_buttons[cur_elem].activate();
            scene->container[scene->cur_elem].deactivate();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (cur_container==1){
            scene->container[scene->cur_elem].up();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (cur_container==1){
            scene->container[scene->cur_elem].down();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (cur_container==1){
            scene->container[scene->cur_elem].left();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (cur_container==1){
            scene->container[scene->cur_elem].right();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS) {
        if (cur_container==1){
            scene->container.erase(scene->container.begin()+scene->cur_elem)[scene->cur_elem];
            std::vector<Map_object<32>> new_container;
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
