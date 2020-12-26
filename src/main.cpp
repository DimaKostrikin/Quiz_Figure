#include "Features_lib/Logic_manager.h"


int main(int argc, char **argv) {
    stbi_set_flip_vertically_on_load(true);

    auto& logic_manager = Logic_manager::instance();
    logic_manager.initialize();
}
