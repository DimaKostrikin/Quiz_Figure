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
            interface.draw_leves();
            std::string lvl_begin_path = "levels/lvl";
            std::string lvl_ending_path = ".json";

            std::string level_path;
            while (!glfwWindowShouldClose(window)) {
                item = interface.cycle();
                if (item) {
                    level_path = lvl_begin_path + std::to_string(item) + lvl_ending_path;
                    break;
                }
            }
            start_game(level_path);
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

void Logic_manager::start_game(const std::string &level_path) {
    // Создание списков объектов
    std::list<Object_dynamic> obj_dyn;
    std::list<Object_static> obj_stat;
    std::list<Object_activated> obj_acted;
    std::list<Object_activator> obj_actor;
    std::list<Object_influence> obj_infl;

    // Стандартные значения характеристик для игрока
    Point default_player_center = {1000, 1000, 1000};
    Size default_player_size = {500, 500, 1000};

    Player player(default_player_center, default_player_size);  // Инициализация игрока

    std::cout << level_path;
    Parser p(obj_dyn, obj_stat, obj_acted, obj_actor, obj_infl);  // Создание парсера для загрузки уровня
    // (!) p.fill_from(level_path);  // Заполнение списков соответственно json файлу.


    // Хендлер фич, обработка внутриигровых эвентов
    auto &hand_feat = Handler_feature::instance(obj_acted, obj_actor, obj_dyn, obj_infl, player);

    /*while (true) {  // TODO main cycle
        hand_feat.do_logic();
        // хендлер физики делает бррр
        // отрисовка объектов делает бррр
    }
    */
}


