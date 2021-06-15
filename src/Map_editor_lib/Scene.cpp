#include "Map_editor_lib/Scene.h"

#include <utility>


Scene::Scene(std::vector<float> vertices): vertices_paper(std::move(vertices)), paper("textures/white.png", vertices), id(0),
cur_elem(0), n(0), save(0), connection_mode(false){}


void Scene::paper_maker() {
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO); // мы также можем генерировать несколько VAO или буферов одновременно
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    paper.draw(VAO, VBO, EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Scene::draw() {
    paper_maker();
    for(auto &i: container)
    {
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
}

void Scene::delete_elem() {
    if (!container.empty()) {
        if (container[cur_elem].is_active()) {
            size_t c = container[cur_elem].id;
            container[cur_elem] = container[container.size()-1];
            container.pop_back();
            for (auto &i: container){
                if (i.connect == c) i.connect = 0;
            }
        }
    }
}

void Scene::scene_action(double &x, double &y, const unsigned int &h, const unsigned int &w) {
    size_t j = 0;
    bool is_not_activated = true;

    // если не соединяем
    if (!connection_mode) {
        for (auto &i: container) {
            i.deactivate();
            double x1 = (i.vertices[16] + 1.0f) * (w / 2);
            double x2 = (i.vertices[0] + 1.0f) * (w / 2);
            double y1 = (1.0f - i.vertices[1]) * (h / 2);
            double y2 = (1.0f - i.vertices[9]) * (h / 2);
            if (is_not_activated) {
                if ((x1 < x) && (x < x2)
                    && (y1 < y) && (y < y2)) {
                    cur_elem = j;
                    i.activate();
                    is_not_activated = false;
                }
            }
            ++j;
        }

        // если соединяем
    } else {
        j = 0;
        for (auto &i: container) {
            double x1 = (i.vertices[16] + 1.0f) * (w / 2);
            double x2 = (i.vertices[0] + 1.0f) * (w / 2);
            double y1 = (1.0f - i.vertices[1]) * (h / 2);
            double y2 = (1.0f - i.vertices[9]) * (h / 2);
            if (n < 2) {
                if ((x1 < x) && (x < x2)
                    && (y1 < y) && (y < y2)) {
                    i.activate();
                    n++;
                    if (n == 1) save = j;
                    else {
                        connect(save, j);
                        container[save].deactivate();
                        container[j].deactivate();
                        n = 0;
                    }
                }
            }
            ++j;
        }
    }
}
void Scene::connect(size_t &i, size_t &j) {
    if (container[i].is_activator()){
        if (container[j].is_activated())
            container[i].connect = container[j].id; // hole открывает финиш
        if (container[j].is_dynamic())
            container[j].connect = container[i].id; // куб открывает hole
    } else if (container[i].is_activated()){
        if (container[j].is_activator())
            container[i].connect = container[j].id; // финиш открывается из-за отверстия
    } else if (container[i].is_dynamic()){
        if (container[j].is_activator())
            container[i].connect = container[j].id; // финиш открывается из-за отверстия
    } else if (container[i].type == TELEPORT_IN) {
        if (container[j].type == TELEPORT_OUT)
            container[i].connect = container[j].id;
    } else if (container[j].type == TELEPORT_IN) {
        if (container[i].type == TELEPORT_OUT)
            container[j].connect = container[i].id;
    }
}



