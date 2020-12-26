#include "Features_lib/Logic_manager.h"

Logic_manager& Logic_manager::instance() {
    static Logic_manager lm;
    return lm;
}

void Logic_manager::initialize() {
    Interface interface;
    window = interface.get_window();  // Класс inteface создал окно, указатель на окно я присвою классу Logic_manager для удобства, чтобы каждый раз геттер не вызывать.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    interface.draw_menu();
    while (!glfwWindowShouldClose(window)) {
        int item = interface.cycle();

        if (item == START_GAME) { // Проверка нажатия на кнопку начать игру
            interface.draw_levels();
            std::string lvl_begin_path = "levels/lvl";
            std::string lvl_ending_path = ".json";

            std::string level_path;
            while (!glfwWindowShouldClose(window)) {
                item = interface.cycle();
                if (item || item == MENU) {
                    level_path = lvl_begin_path + std::to_string(item) + lvl_ending_path;
                    break;
                }
            }
            if (item == MENU) {
                interface.draw_menu();
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
            else start_game(level_path);
        }
        if (item == REDACTOR) {  // Проверка нажатия на кнопку редактора
            interface.draw_redactor();
            while (!glfwWindowShouldClose(window) && item != MENU) {
                item = interface.cycle();
            }
            interface.draw_menu();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        }
        if (item == EXIT) {  // Проверка нажатия на кнопку выхода
            break;
        }
    }
    glfwTerminate();
}

void Logic_manager::start_game(const std::string &level_path) {
    // Создание списков объектов
    std::list<Object_dynamic> obj_dyn;
    std::list<Object_static> obj_stat;
    std::list<Object_activated> obj_acted;
    std::list<Object_activator> obj_actor;
    std::list<Object_influence> obj_infl;



    // Стандартные значения характеристик для игрока
    glm::vec3 default_player_center = {1, 2, 3};
    glm::vec3 default_player_size = {0.5, 0.5, 0.5};


    Player player(default_player_center, default_player_size);  // Инициализация игрока


    Parser p(obj_dyn, obj_stat, obj_acted, obj_actor, obj_infl);  // Создание парсера для загрузки уровня
    p.fill_from(level_path);  // Заполнение списков соответственно json файлу.

    // Хендлер фич, обработка внутриигровых эвентов
    auto &hand_feat = Handler_feature::instance(obj_acted, obj_actor, obj_dyn, obj_infl, player);





    Render_manager render_mng(obj_dyn, obj_stat, obj_acted, obj_actor, obj_infl);
    Shader ourShader("Shader_files/shader.vs", "Shader_files/shader.fs");

    //заполняем вектор источников света вручную(для примера, пока не объединили код)
    std::vector <Point_light> point_lights;
    render_mng.setup_camera(glm::vec3(0.f, 0.5f, 3.f));
    glm::vec3 pointLightPositions[] = {
            glm::vec3( -3.0f,  1.0f,  5.0f),
            glm::vec3( -5.0f, 1.0f, 5.0f),
            glm::vec3(-5.0f,  1.0f, 3.0f),
            glm::vec3( -5.0f,  1.0f, 1.0f)
    };


    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Handler_physics hand_phys(obj_dyn, obj_stat, obj_acted, obj_actor, player, render_mng.get_camera().Front, window);

    //зполняем вектор источников света значениями
    for (size_t i = 0; i < 4; ++i) {
        point_lights.push_back(Point_light(pointLightPositions[i]));
    }

    double lastFrame = 0;
    double currentFrame = glfwGetTime();
    double deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    while (!glfwWindowShouldClose(window)) {  // TODO main cycle

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (deltaTime > 0.01) {
            deltaTime = 0.01;
        }
        for (auto it = obj_dyn.begin(); it != obj_dyn.end(); ++it) {
            if (it->get_elem_type() == BALL && it->get_center().z < 10)  {
                // std::cout << it->get_center().z << std::endl;
                //std::cout << it->get_speed().z << "time is " << deltaTime << std::endl;
            }
            it->update_model();
        }

        hand_feat.do_logic(deltaTime);  // Эвенты


        hand_phys.update(deltaTime);  // Физика
        render_mng.process_render(window, ourShader, point_lights);  // Отрисовка



        render_mng.get_camera().Position.x = (float)player.get_center().x;

        render_mng.get_camera().Position.z = (float)player.get_center().y;

        render_mng.get_camera().Position.y = (float)player.get_center().z;


        hand_phys.camera = render_mng.get_camera().Front;

    }
}


