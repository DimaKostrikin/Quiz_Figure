//
// Created by moroz on 23.12.2020.
//

#include "gtest/gtest.h"
#include "Elements.h"

TEST(functions, ok) {
    std::vector<float>vertices = {
            // координаты

            0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // верхняя правая
            0.7f, -0.7f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // нижняя правая
            -0.7f, -0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.7f, 0.7f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };
    Elem paper("textures/white.png", vertices);

    // отрисовка
    paper.draw();

    Button_entry button_start("textures/start_text.png", "textures/start_text_act.png", vertices);

    // смена текстур
    button_start.activate();
    ASSERT_EQ(button_start.get_texture(), button_start.get_act_texture());
    button_start.deactivate();
    ASSERT_EQ(button_start.get_texture(), button_start.get_pas_texture());



}