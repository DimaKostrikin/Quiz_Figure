#include "Map_editor_lib/Elements.h"

//генерация текстуры
void Elem::texture_gen(unsigned int &texture, const std::string& filename){
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // загрузка изображения, создание текстуры и генерирование mipmap-уровней
    int width, height, nrChannels;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Elem::draw(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
    unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
    };
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    float new_vertices[N];

    for ( size_t i = 0; i < N; ++i )
        new_vertices[i] = vertices[i];
    glBufferData(GL_ARRAY_BUFFER, sizeof(new_vertices), new_vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // цветовые атрибуты
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // атрибуты текстурных координат
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, texture_cur);


    // Рендеринг
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void Button_entry::set_texture(unsigned int texture){
    texture_cur = texture;
}

void Button_entry::activate(){
    set_texture(texture_active);
    activated = true;
}


void Button_entry::deactivate(){
    set_texture(texture_passive);
    activated = false;
}

unsigned int Button_entry::get_texture() {
    return texture_cur;
}

unsigned int Button_entry::get_act_texture() {
    return texture_active;
}

unsigned int Button_entry::get_pas_texture() {
    return texture_passive;
}

void Map_object::up(const unsigned int &h){
    if (this->vertices[1] < 0.7f) {
        this->vertices[1] += 0.01f;
        this->vertices[9] += 0.01f;
        this->vertices[17] += 0.01f;
        this->vertices[25] += 0.01f;
        change_y(h);
    }
}
void Map_object::down(const unsigned int &h){
    if (this->vertices[17] > -0.7f) {
        this->vertices[1] -= 0.01f;
        this->vertices[9] -= 0.01f;
        this->vertices[17] -= 0.01f;
        this->vertices[25] -= 0.01f;
        change_y(h);
    }
}

void Map_object::right(const unsigned int &w){
    if (this->vertices[0] < 0.7f) {
        this->vertices[0] += 0.01f;
        this->vertices[8] += 0.01f;
        this->vertices[16] += 0.01f;
        this->vertices[24] += 0.01f;
        change_x(w);
    }
}
void Map_object::left(const unsigned int &w){
    if (this->vertices[16] > -0.7f) {
        this->vertices[0] -= 0.01f;
        this->vertices[8] -= 0.01f;
        this->vertices[16] -= 0.01f;
        this->vertices[24] -= 0.01f;
        change_x(w);
    }
}

Map_object &Map_object::operator=(const Map_object &elem) {
    texture_passive = elem.texture_passive;
    texture_active = elem.texture_active;
    texture_cur = elem.texture_cur;
    activated = elem.activated;
    id = elem.id;
    vertices = elem.vertices;
    type = elem.type;
    return *this;
}

bool Map_object::is_activator() const {
    return ((type == HOLE) || (type == STEP));
}

bool Map_object::is_activated() const {
    return ((type == DOOR) || (type == BUTTON) || (type == FINISH)
    || (type == TELEPORT_IN));
}

bool Map_object::is_dynamic() const {
    return ((type == CUBE) || (type == BALL));
}

bool Map_object::is_static() const {
    return ((type == PLATFORM) || (type == WALL));
}

//
bool Map_object::is_connected() const {
    return (type == JUMPER);
}



void Map_object::up_z() {
    z += 10;
}

void Map_object::down_z() {
    if (z>0) {
        z -= 10;
    }
}

void Map_object::plus_width(float &rborder, float &lborder, float &tborder, float &bborder, const unsigned int &w) {
    if (check_border(rborder, lborder, tborder, bborder)) {
        vertices[1] += 0.01f;
        vertices[9] -= 0.01f;
        vertices[17] -= 0.01f;
        vertices[25] += 0.01f;
    } else if (!check_border_up(tborder) && check_border_down(bborder)){
        vertices[9] -= 0.01f;
        vertices[17] -= 0.01f;
    } else if (!check_border_down(bborder) && check_border_up(tborder)){
        vertices[1] += 0.01f;
        vertices[25] += 0.01f;
    }
    change_w(w);

}

void Map_object::minus_width(const unsigned int &w) {
    if (check_elem()) {
        vertices[1] -= 0.01f;
        vertices[9] += 0.01f;
        vertices[17] += 0.01f;
        vertices[25] -= 0.01f;
        change_w(w);
    }
}

void Map_object::plus_length(float &rborder, float &lborder, float &tborder, float &bborder, const unsigned int &h) {
    if (check_border(rborder, lborder, tborder, bborder)) {
        vertices[0] += 0.01f;
        vertices[8] += 0.01f;
        vertices[16] -= 0.01f;
        vertices[24] -= 0.01f;
    } else if (!check_border_left(lborder) && check_border_right(rborder)){
        vertices[0] += 0.01f;
        vertices[8] += 0.01f;
    } else if (!check_border_right(rborder) && check_border_left(lborder)){
        vertices[16] -= 0.01f;
        vertices[24] -= 0.01f;
    }
    change_l(h);

}

void Map_object::minus_length(const unsigned int &h) {
    if (check_elem()) {
        vertices[0] -= 0.01f;
        vertices[8] -= 0.01f;
        vertices[16] += 0.01f;
        vertices[24] += 0.01f;
        change_l(h);
    }
}
bool Map_object::check_elem() {
    return ((vertices[0] - vertices[16]) >= 0.05f && (vertices[1] - vertices[9])>=0.05f);
}

bool Map_object::check_border_right(float &border) {
    return vertices[0] < border;
}

bool Map_object::check_border_left(float &border) {
    return vertices[16] > border;
}

bool Map_object::check_border_up(float &border) {
    return vertices[1] < border;
}

bool Map_object::check_border_down(float &border) {
    return vertices[9] > border;
}

bool Map_object::check_border(float &rborder, float &lborder, float &tborder, float &bborder) {
    return (check_border_left(lborder) && check_border_down(bborder)
            && check_border_right(rborder) && check_border_up(tborder));
}

void Map_object::change_w(const unsigned int &h) {
    double y1 = (0.7f - vertices[1]) * (h / 2);
    double y2 = (0.7f - vertices[9]) * (h / 2);
    this->w = floor(y2 - y1);
}

void Map_object::change_l(const unsigned int &w) {
    double x1 = (0.7f + vertices[16]) * (w / 2);
    double x2 = (0.7f + vertices[0]) * (w / 2);
    this->l = floor(x2 - x1);
}

void Map_object::change_x(const unsigned int &w) {
    double x1 = (vertices[16]) * (w / 2);
    double x2 = (vertices[0] ) * (w / 2);
    this->x = floor(x1+(x2 - x1)/2);
}

void Map_object::change_y(const unsigned int &h) {
    double y1 = (vertices[1]) * (h / 2);
    double y2 = ( vertices[9]) * (h / 2);
    this->y = floor(y1+(y2 - y1)/2);
}


void Map_object::minus_height() {
    if (h > 0){
        h-=10;
    }
}

void Map_object::plus_height() {
    h += 10;
}

Map_object::Map_object(std::string f1, std::string f2, std::vector<float> vertices, type_elem type, size_t id,
                       const unsigned int &SCR_HEIGHT, const unsigned int &SCR_WIDTH) :
        Button_entry(std::move(f1), std::move(f2), std::move(vertices)),
        id(id), connect(0),type(type), z(0), h(3){
    change_w(SCR_WIDTH);
    change_l(SCR_HEIGHT);
    change_x(SCR_WIDTH);
    change_y(SCR_HEIGHT);

}


