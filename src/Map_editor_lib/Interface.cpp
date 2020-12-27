#include "Map_editor_lib/Interface.h"


// edited by DimaKostrikin

int Interface::cycle() {
    int choose = processInput();

    draw();
    // glfw: обмен содержимым front- и back- буферов. Отслеживание событий Ввода\Вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
    glfwSwapBuffers(window);
    glfwPollEvents();
    return choose;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в данном кадре и соответствующая обработка данных событий


// glfw: всякий раз, когда изменяются размеры окна (пользователем или оперионной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // Убеждаемся, что окно просмотра соответствует новым размерам окна
    // Обратите внимание, что ширина и высота будут значительно больше, чем указано на Retina-дисплеях
    glViewport(0, 0, width, height);
}

Interface::~Interface() = default;

Interface::Interface() {
    // glfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: создание окна
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FigureQuiz", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    menu = std::make_shared<Menu>(window);
    levels = std::make_shared<Levels>(window);
    map_editor = std::make_shared<Map_editor_handler>(window, SCR_HEIGHT, SCR_WIDTH);
}

GLFWwindow *Interface::get_window() {
    return window;
}

void Interface::draw_menu() {
    draw = menu->draw;
    processInput = menu->processInput;
}

void Interface::draw_levels() {
    draw = levels->draw;
    processInput = levels->processInput;
}

void Interface::draw_redactor() {
    draw = std::bind(&Map_editor_handler::draw, map_editor);
    processInput = std::bind(&Map_editor_handler::processInput, map_editor);
}

void dwin(){
    std::vector<float>vertices = {
            // координаты

            1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
            1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
            -1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };
    Elem win("textures/win.png", vertices);
    Shader shader("include/Map_editor_lib/shader.vs", "include/Map_editor_lib/shader.fs");
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    shader.use();
    win.draw(VAO, VBO, EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}


void Interface::draw_win() {
    draw = dwin;
}







