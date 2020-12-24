#include "Features_lib/Logic_manager.h"


int main(int argc, char **argv) {
    auto& logic_manager = Logic_manager::instance();
    logic_manager.initialize();
}
