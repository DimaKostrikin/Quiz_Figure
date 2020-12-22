#include "Map_editor_handler.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 1280;

Map_editor_handler::Map_editor_handler() : window(nullptr),
    SCR_WIDTH(0), SCR_HEIGHT(0), shader(Shader("shader.vs", "shader.fs")),
    last_frame(0), delta(0), cur_elem(0), parser(0,0){
    toolbar_init();
}

Map_editor_handler::Map_editor_handler(GLFWwindow *window, const unsigned int &SCR_HEIGHT,
    const unsigned int &SCR_WIDTH) : window(window), SCR_HEIGHT(SCR_HEIGHT),
    SCR_WIDTH(SCR_WIDTH), shader(Shader("shader.vs", "shader.fs")),
    last_frame(0), delta(0), cur_elem(0),
    label(std::make_shared<Parameters_label>()), parser(0,0){
    std::vector<float>vertices = {
            // координаты

            0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.7f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
            -0.7f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.7f, 0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };
    scene = std::make_shared<Scene>(vertices);

    double x1 = (vertices[16] + 1.0f) * (SCR_WIDTH / 2);
    double x2 = (vertices[0] + 1.0f ) * (SCR_WIDTH / 2);
    unsigned int w = floor(x2 - x1);
    double y1 = (1.0f - vertices[1]) * (SCR_HEIGHT / 2);
    double y2 = (1.0f - vertices[9]) * (SCR_HEIGHT / 2);
    unsigned int l = floor(y2 - y1);
    parser = Map_parser(l, w);
    toolbar_init();

}


void Map_editor_handler::toolbar_init() {
    std::vector<std::vector<float>> coordinates_square;
    std::vector<std::vector<float>> coordinates_rectangle;
    std::vector<std::vector<float>> texts;
    std::vector<float> vertices_button {
            // координаты

            -0.75f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.75f, 0.8f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.95f, 0.8f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.95f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    for (int i=0; i < 10; ++i){
        coordinates_square.push_back(vertices_button);
        vertices_button[1]-=0.2f;
        vertices_button[9]-=0.2f;
        vertices_button[17]-=0.2f;
        vertices_button[25]-=0.2f;
    }
    std::vector<float> vertices_button_rec {
            // координаты
            -0.35f,  -0.75f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            -0.35f, -0.95f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.65f, -0.95f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.65f, -0.75f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    for (int i=0; i < 2; ++i){
        coordinates_rectangle.push_back(vertices_button_rec);
        vertices_button_rec[0]+=0.4f;
        vertices_button_rec[8]+=0.4f;
        vertices_button_rec[16]+=0.4f;
        vertices_button_rec[24]+=0.4f;
    }

    toolbar_buttons.emplace_back("textures/start_icon.png", "textures/start_icon_act.png",coordinates_square[0], START);
    toolbar_buttons.emplace_back("textures/finish_icon.png", "textures/finish_icon_act.png", coordinates_square[1], FINISH);
    toolbar_buttons.emplace_back("textures/static_wall_icon.png", "textures/static_wall_icon_act.png", coordinates_square[2], WALL_STATIC);
    toolbar_buttons.emplace_back("textures/cube_icon.png", "textures/cube_icon_act.png", coordinates_square[3], CUBE);
    toolbar_buttons.emplace_back("textures/hole_icon.png", "textures/hole_icon_act.png", coordinates_square[4], HOLE);
    toolbar_buttons.emplace_back("textures/jumper_icon.png", "textures/jumper_icon_act.png", coordinates_square[5], JUMPER);
    toolbar_buttons.emplace_back("textures/wall_icon.png", "textures/wall_icon_act.png", coordinates_square[6], WALL);
    toolbar_buttons.emplace_back("textures/platform_icon.png", "textures/platform_icon_act.png", coordinates_square[7], PLATFORM);
    toolbar_buttons.emplace_back("textures/teleport_in_icon.png", "textures/teleport_in_icon_act.png", coordinates_square[8], TELEPORT_IN);
    toolbar_buttons.emplace_back("textures/teleport_out_icon.png", "textures/teleport_out_icon_act.png", coordinates_square[9], TELEPORT_OUT);
    toolbar_buttons.emplace_back("textures/delete_text.png", "textures/delete_text_act.png", coordinates_rectangle[0], DELETE);
    toolbar_buttons.emplace_back("textures/save_text.png", "textures/save_text_act.png", coordinates_rectangle[1], SAVE);
}

void Map_editor_handler::draw() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.use();
    glClearColor(0.51f, 0.73f, 0.73f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    scene->draw();

    for (auto &i: toolbar_buttons) {
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

    if (!scene->container.empty()) {
        if (scene->container[scene->cur_elem].is_active()) {
            label->set_object(std::make_shared<Map_object>(scene->container[scene->cur_elem]));
        } else label->set_object(nullptr);
    }
    label->draw();


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


// разбить на подфункции


void Map_editor_handler::processInput() {
    double current_frame = glfwGetTime();
    double delta_time = current_frame - last_frame;
    last_frame = current_frame;
    delta += delta_time;


    double x, y;

    glfwGetCursorPos(window, &x, &y);
    int j = 0;

    // подсвечивание тулбара слева
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

    // Выход
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Обработчик нажатия

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (delta > 0.1f) {
            delta=0;
            // нажатие на тулбар слева
            if (toolbar_buttons[cur_elem].is_active() && (!scene->connection_mode)) {
                toolbar_left_action(x, y);
            } else scene->scene_action(x, y); // нажатие на элемент сцены
        }
    }

//

    if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE) &&
            (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE)&&
            (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active())
                scene->container[scene->cur_elem].up();
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f)) {
                delta = 0;
                scene->container[scene->cur_elem].minus_width();
            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) &&
            (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f))
            {
                delta=0;
                scene->container[scene->cur_elem].plus_width(scene->vertices_paper[0], scene->vertices_paper[16],
                                                             scene->vertices_paper[1], scene->vertices_paper[9]);

            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f)) {
                delta = 0;
                scene->container[scene->cur_elem].minus_length();
            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) &&
        (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f))
            {
                delta=0;
                scene->container[scene->cur_elem].plus_length(scene->vertices_paper[0], scene->vertices_paper[16],
                                                              scene->vertices_paper[1], scene->vertices_paper[9]);
            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) &&
        (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f))
            {
                delta=0;
                scene->container[scene->cur_elem].up_z();
            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f))
            {
                delta=0;
                scene->container[scene->cur_elem].down_z();
            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) &&
        (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f))
            {
                delta=0;
                scene->container[scene->cur_elem].plus_height();
            }
        }
    }

    if ((glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) && (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active() && (delta>0.1f))
            {
                delta=0;
                scene->container[scene->cur_elem].minus_height();
            }
        }
    }


    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active())
                scene->container[scene->cur_elem].down();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active())
                scene->container[scene->cur_elem].left();
        }
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (!scene->container.empty()) {
            if (scene->container[scene->cur_elem].is_active())
                scene->container[scene->cur_elem].right();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        scene->container[scene->cur_elem].deactivate();
        scene->connection_mode = true;
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        scene->connection_mode = false;
    }

}


void Map_editor_handler::toolbar_left_action(double &x, double &y) {
    std::vector<float> vertices_button{
            // координаты

            0.2f, 0.2f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // верхняя правая
            0.2f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // нижняя правая
            0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // нижняя левая
            0.0f, 0.2f, 0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 1.0f

    };


    switch (toolbar_buttons[cur_elem].type) {
        case START: {
            scene->container.emplace_back(Map_object
                                                  ("textures/start.png", "textures/start_act.png", vertices_button,
                                                   START, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case FINISH: {
            scene->container.emplace_back(Map_object
                                                  ("textures/exit.png", "textures/exit_act.png", vertices_button,
                                                   FINISH, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case HOLE: {
            scene->container.emplace_back(Map_object
                                                  ("textures/hole.png", "textures/hole_act.png", vertices_button,
                                                   HOLE, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case CUBE: {
            scene->container.emplace_back(Map_object
                                                  ("textures/cube.png", "textures/cube_act.png", vertices_button,
                                                   CUBE, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case PLATFORM: {
            scene->container.emplace_back(Map_object
                                                  ("textures/platform.png", "textures/platform_act.png", vertices_button,
                                                   PLATFORM, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case JUMPER: {
            scene->container.emplace_back(Map_object
                                                  ("textures/jumper.png", "textures/jumper_act.png", vertices_button,
                                                   JUMPER, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case TELEPORT_IN: {
            scene->container.emplace_back(Map_object
                                                  ("textures/teleport_in.png", "textures/teleport_in_act.png", vertices_button,
                                                   TELEPORT_IN, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case TELEPORT_OUT: {
            scene->container.emplace_back(Map_object
                                                  ("textures/teleport_out.png", "textures/teleport_out_act.png", vertices_button,
                                                   TELEPORT_OUT, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case WALL_STATIC: {
            scene->container.emplace_back(Map_object
                                                  ("textures/black.png", "textures/blue.png", vertices_button,
                                                   WALL_STATIC, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case WALL: {
            scene->container.emplace_back(Map_object
                                                  ("textures/wall.png", "textures/wall_act.png", vertices_button,
                                                   WALL, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
            break;
        }
        case SAVE: {
            if (scene->container.size() > 0)
                parser.create_json(scene->container);
            break;
        }
        case DELETE: {
            scene->delete_elem();
            break;
        }
        default:
            break;
    };
}


