#include "Features_lib/Logic_manager.h"

Logic_manager& Logic_manager::instance() {
    static Logic_manager lm;
    return lm;
}

void Logic_manager::initialize() {
    Interface interface;
    glfwSetInputMode(interface.get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    interface.draw_menu();
    while (!glfwWindowShouldClose(interface.get_window())) {

        int item = interface.cycle();

        if (item == START_GAME) { // ПРоверка нажатия на кнопку начать игру
            std::cout << "Game start" << std::endl;
            interface.draw_leves();
            //start_game();
        }
        if (item == REDACTOR) { // Проверка нажатия на кнопку редактора
            std::cout << "Redactor start" << std::endl;
            //start_redactor();  // Повызывай методы, которые тебе нужны внутри этой функции
        }
        if (item == EXIT) {  // Проверка нажатия на кнопку выхода
            break;
        }
    }
    //glfwTerminate();  Это нужно зачем-то? Я не понял для чего. Оно работает и без этого.
}

void Logic_manager::start_game() {
    // Создание списков объектов
    std::list<Object_dynamic> obj_dyn;
    std::list<Object_static> obj_stat;
    std::list<Object_activated> obj_acted;
    std::list<Object_activator> obj_actor;
    std::list<Object_influence> obj_infl;

    // Стандартные значения характеристик для игрока
    Point default_player_center = {1000, 1000, 1000};
    Size default_player_size = {500, 500, 1000};

    Player player(default_player_center, default_player_size);


    Parser p(obj_dyn, obj_stat, obj_acted, obj_actor, obj_infl);
    p.fill_from("json.json");
    // Функция выбора уровня

    //std::string(choose_level());
    //std::string("path");


    // Функция инициализации списков из файла json (парсер короче)

    auto &hand_feat = Handler_feature::instance(obj_acted, obj_actor, obj_dyn, obj_infl, player);

    while (true) {
        hand_feat.do_logic();
        // хендлер физики делает бррр
        // отрисовка объектов делает бррр
    }
}


