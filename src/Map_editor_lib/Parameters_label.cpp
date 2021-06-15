#include "Map_editor_lib/Parameters_label.h"

#include <utility>

Parameters_label::Parameters_label(const unsigned int SCR_HEIGHT, const unsigned int SCR_WIDTH) :
obj(nullptr), SCR_HEIGHT(SCR_HEIGHT), SCR_WIDTH(SCR_WIDTH),
shader(Shader("include/Map_editor_lib/text.vs", "include/Map_editor_lib/text.fs")){

    // FreeType
    // --------
    FT_Library ft;
    // Всякий раз, когда возникает ошибка, функции будут возвращать отличное от нуля значение
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    // путь к файлу шрифта
    std::string font_name = "fonts/courier_new.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
    }

    // загружаем шрифт в face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else {
        // задаем размер для загрузки глифов
        FT_Set_Pixel_Sizes(face, 0, 48);

        // отключаем ограничение выравнивания байтов
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // загружаем глифы символов
        for (unsigned int c = 0; c < 256; c++)
        {
            // загружаем глиф символа
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // генерируем текстуру
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );
            // задаём для текстуры необходимые опции
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // теперь сохраняем символ для последующего использования
            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
            };
            characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // освобождаем использованные ресурсы
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}



void Parameters_label::draw() {

    // состояние OpenGL
    // ------------

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int VAO, VBO;

    // компилируем и устанавливаем шейдер
    // ----------------------------
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // конфигурируем VAO/VBO для текстурных прямоугольников
    // -----------------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // хардкод кривоой
    float tx = (float)SCR_WIDTH*0.87f;
    float y = (float)SCR_HEIGHT;
    float coef = 0.4f;
    glm::vec3 black_color = glm::vec3(0.0f, 0.0f, 0.0f);
    const std::string help_text = "Help text: to change height, width, length, z - ";
    RenderText(VAO, VBO, shader, help_text, 200, (float)y*0.95, coef, black_color);
    const std::string help_text2 = "push first letter of the word with - or +";
    RenderText(VAO, VBO, shader, help_text2, 400, (float)y*0.91, coef, black_color);
    const std::string help_text3 = "Press c and select two elements to connect them";
    RenderText(VAO, VBO, shader, help_text3, 200, (float)y*0.87, coef, black_color);
    //внимание! здесь считаем от левого нижнего угла. убрать хардкод
    if (obj) {
        RenderText(VAO, VBO, shader, "ID: " + std::to_string(obj->id), tx, y, coef, black_color);
        RenderText(VAO, VBO, shader, "X: " + std::to_string(obj->x), tx, (float)y*0.95, coef, black_color);
        RenderText(VAO, VBO, shader, "Y: " + std::to_string(obj->y), tx, (float)y*0.91, coef, black_color);
        RenderText(VAO, VBO, shader, "Z: " + std::to_string(obj->z) , tx, (float)y*0.87, coef, black_color);
        RenderText(VAO, VBO, shader, "Width: " + std::to_string(obj->w), tx, (float)y*0.83, coef, black_color);
        RenderText(VAO, VBO, shader, "Length: " + std::to_string(obj->l), tx, (float)y*0.79, coef, black_color);
        RenderText(VAO, VBO, shader, "Height: " + std::to_string(obj->h), tx, (float)y*0.75, coef, black_color);
        RenderText(VAO, VBO, shader, "Connect: " + std::to_string(obj->connect), tx, (float)y*0.71, coef, black_color);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);

}

// рендер строки текста
// -------------------
void Parameters_label::RenderText(unsigned int &VAO, unsigned int &VBO, Shader& shader, std::string text,
                                  float x, float y, float scale, glm::vec3 color)
{
    // активируем соответствующее состояние рендеринга
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // перебираем все символы
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // обновляем VBO для каждого символа
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // рендер текстуру глифа на прямоугольник
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // обновляем содержимое памяти VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // обязательно используйте glBufferSubData, а не glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // рендер прямоугольника
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // теперь производим смещение для отображения следующего глифа (обратите внимание, что данное смещение измеряется в единицах, составляющих 1/64 пикселя)
        x += (ch.Advance >> 6) * scale; // битовый сдвиг на 6 разрядов, чтобы получить значение в пикселях (2^6 = 64 (разделите количество 1/64-х пикселей на 64, чтобы получить количество пикселей))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Parameters_label::set_object(std::shared_ptr<Map_object> object) {
    this->obj = std::move(object);
}

std::shared_ptr<Map_object> Parameters_label::get_object() {
    return obj;
}


