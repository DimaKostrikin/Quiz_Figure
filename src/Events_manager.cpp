#include "Events_manager.h"

Events_manager::Events_manager() {
    std::map <std::string, bool> :: iterator it = control_tools.begin();
    for (; it != control_tools.end(); it++) {
        prev_control_tools[it->first] = !it->second;
    }
}

void Events_manager::processInput(GLFWwindow *window, Camera &camera, float delta_time)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, delta_time, control_tools);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, delta_time, control_tools);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, delta_time, control_tools);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, delta_time, control_tools);

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        change_state("Carcass");
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
        prev_control_tools["Carcass"] = !prev_control_tools["Carcass"];

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        change_state("Flashlight");
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        prev_control_tools["Flashlight"] = !prev_control_tools["Flashlight"];

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        change_state("Flight");
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE)
        prev_control_tools["Flight"] = !prev_control_tools["Flight"];
}

void Events_manager::change_state(std::string key) {
    if (control_tools[key] != prev_control_tools[key])
        control_tools[key] = !control_tools[key];
}

bool Events_manager::get(std::string key) {
    return control_tools[key];
}
