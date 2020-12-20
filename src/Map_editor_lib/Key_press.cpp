#include "Map_editor_lib/Key_press.h"


bool Key_press(const int &key, GLFWwindow *window, bool &state) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        if (state == false) {
            state = true;
            return false;
        }
    } else {
        if (state == true) {
            state = false;
            return true;
        }
    }
    return false;
}
