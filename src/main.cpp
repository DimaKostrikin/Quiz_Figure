#include "Map_editor_lib/Interface.h"
#include "Features_lib/Logic_manager.h"
#include "Features_lib/Objects.h"


int main(int argc, char **argv) {
    auto& logic_manager = Logic_manager::instance();
    logic_manager.initialize();
}
