#include <iostream>
#include "Objects.h"

int main() {
    Point player_center = {0, 2, 0};
    Size player_sizes = {100, 50, 100};
    Speed player_speed = {0, 1, 2};
    Player player(player_center, player_sizes);

    std::cout << player.get_speed();

    Object_influence jump(JUMPER, player_center, player_sizes, player);
    jump.update_player();
    std::cout << player.get_speed();

    Object_activated door(DOOR, player_center, player_sizes);
    Object_activator button(BUTTON, player_center, player_sizes, door);
    std::cout << door.is_activated() << std::endl;
    button.activate_linked_object();
    std::cout << door.is_activated() << std::endl;
    return 0;
}
