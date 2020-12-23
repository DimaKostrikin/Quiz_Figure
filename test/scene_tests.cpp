//
// Created by moroz on 23.12.2020.
//

#include "gtest/gtest.h"
#include "Scene.h"

TEST(functions, ok) {
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 1024;

    std::vector<float>vertices = {
            // координаты

            0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.7f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
            -0.7f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.7f, 0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    Scene scene(vertices);
    scene.container.emplace_back(Map_object
            ("textures/start.png", "textures/start_act.png", vertices_button,
             START, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
    scene.container.emplace_back(Map_object
                                          ("textures/exit.png", "textures/exit_act.png", vertices_button,
                                           FINISH, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
    scene.container.emplace_back(Map_object
                                          ("textures/hole.png", "textures/hole_act.png", vertices_button,
                                           HOLE, ++scene->id, SCR_HEIGHT, SCR_WIDTH));
    scene.container.emplace_back(Map_object
                                          ("textures/cube.png", "textures/cube_act.png", vertices_button,
                                           CUBE, ++scene->id, SCR_HEIGHT, SCR_WIDTH));

    // соединение
    scene->connect(scene.container[1], scene.container[2]);
    ASSERT_EQ(scene.container[1].connect, 3);

    // удаление
    scene.cur_elem = 3;
    scene.container[scene.cur_elem].activate();
    scene.delete_elem();
    ASSERT_EQ(scene.container[1].connect, 0);
    ASSERT_EQ(scene.container.size(), 3);

    // отрисовка
    scene.draw();

    // погашение элементов
    scene.cur_elem = 0;
    scene.container[scene.cur_elem].activate();
    scene.scene_action(0, 0, SCR_HEIGHT, SCR_WIDTH);
    ASSERT_EQ(scene.container[0].is_active(), false);


}
