#include "Graphics_lib/Render_manager.h"

//Render_manager::Render_manager() {
//    ev_manager = Events_manager(nullptr);
//    setup_camera();
//}

Render_manager::Render_manager(std::list<Object_dynamic>& object_dyn, std::list<Object_static>& object_stat,
                               std::list<Object_activated>& object_acted, std::list<Object_activator>& object_actor, std::list<Object_influence>& object_infl)
        : obj_dyn(object_dyn), obj_stat(object_stat), obj_acted(object_acted), obj_actor(object_actor), obj_infl(object_infl) {

}

bool Render_manager::preparation(GLFWwindow* window) {

    //glfw: настройка окна
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

//     говорим stb_image.h чтобы он перевернул загруженные текстуры относительно y-оси (до загрузки модели).
//        stbi_set_flip_vertically_on_load(true);

    //включаем Z-буфер
    glEnable(GL_DEPTH_TEST);

    //захват курсора
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или оперионной системой), вызывается данная callback-функция
void Render_manager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна
    glViewport(0, 0, width, height);
}

// отрисовка
void Render_manager::render(Shader cur_shader_prog, Model cur_model, std::vector <Point_light> point_lights, bool is_light_source)  {

    cur_shader_prog.use();

    // преобразования Вида/Проекции
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
    glm::mat4 view = camera.get_view_matrix();
    cur_shader_prog.setMat4("projection", projection);
    cur_shader_prog.setMat4("view", view);

    // рендеринг загруженной модели
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(cur_model.get_xpos(), cur_model.get_ypos(), cur_model.get_zpos()));
    model = glm::rotate(model, glm::radians(cur_model.get_xangle()), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(cur_model.get_yangle()), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(cur_model.get_zangle()), glm::vec3(0.0, 0.0, 1.0));

    model = glm::scale(model, glm::vec3(cur_model.get_xscale(), cur_model.get_yscale(), cur_model.get_zscale()));
    cur_shader_prog.setMat4("model", model);
    cur_model.draw(cur_shader_prog, camera, ev_manager.control_tools, point_lights, is_light_source);
}

void Render_manager::setup_camera() {
    camera = Camera();
    ev_manager = Events_manager(&camera);
}

void Render_manager::setup_camera(glm::vec3 position) {
    camera = Camera(position);
    ev_manager = Events_manager(&camera);
}

void Render_manager::setup_camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    camera = Camera(position, up, yaw, pitch);
    ev_manager = Events_manager(&camera);
}

void Render_manager::setup_camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    camera = Camera(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
    ev_manager = Events_manager(&camera);
}

//для работы со списками объектов:
void Render_manager::process_render(GLFWwindow* window, Shader shader, std::vector <Point_light> point_lights) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Обработка ввода
    ev_manager.processInput(window, deltaTime);

    // отрисовка в режиме каркаса
    if (ev_manager.control_tools["Carcass"]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Очищаем цветовой буфер  и Z-буфер
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto it = obj_dyn.begin(); it != obj_dyn.end(); it++) {
        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
        render(shader, it->get_model(), point_lights, false);
    }
    for (auto it = obj_stat.begin(); it != obj_stat.end(); it++) {
        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
        render(shader, it->get_model(), point_lights, false);
    }
    for (auto it = obj_acted.begin(); it != obj_acted.end(); it++) {
        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
        render(shader, it->get_model(), point_lights, false);
    }
    for (auto it = obj_actor.begin(); it != obj_actor.end(); it++) {
        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
        render(shader, it->get_model(), point_lights, false);
    }
    for (auto it = obj_infl.begin(); it != obj_infl.end(); it++) {
        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
        render(shader, it->get_model(), point_lights, false);
    }

//    for (size_t i = 0; i < models_vec.size(); i++) {
//        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
//        render(shader, models_vec[i], point_lights, false);
//    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

//для работы с вектором моделей:
void Render_manager::process_render(GLFWwindow* window, Shader shader, std::vector <Point_light> point_lights, std::vector <Model> models_vec) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Обработка ввода
    ev_manager.processInput(window, deltaTime);

    // отрисовка в режиме каркаса
    if (ev_manager.control_tools["Carcass"]) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Очищаем цветовой буфер  и Z-буфер
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for (size_t i = 0; i < models_vec.size(); i++) {
        //если на данной итерации обрабатывается объект-лапмочка, то последним аргументом передавать true
        render(shader, models_vec[i], point_lights, false);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Render_manager::clear() {
    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
}

Camera &Render_manager::get_camera() {
    return camera;
}
