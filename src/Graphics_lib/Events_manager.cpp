#include "Graphics_lib/Events_manager.h"

Events_manager::Events_manager() {
    Events_manager(nullptr);
}

Events_manager::Events_manager(Camera* camera_ptr) {
    _camera_ptr = camera_ptr;

    std::map <std::string, bool> :: iterator it = control_tools.begin();
    for (; it != control_tools.end(); it++) {
        prev_control_tools[it->first] = !it->second;
    }
}

void Events_manager::processInput(GLFWwindow *window, float delta_time)
{
    mouse_callback(window);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _camera_ptr->process_keyboard(FORWARD, delta_time, control_tools);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _camera_ptr->process_keyboard(BACKWARD, delta_time, control_tools);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _camera_ptr->process_keyboard(LEFT, delta_time, control_tools);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _camera_ptr->process_keyboard(RIGHT, delta_time, control_tools);

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
    if (control_tools[key] != prev_control_tools[key]) {
        control_tools[key] = !control_tools[key];
        if (control_tools[key]) std::cout << key << " ON" << std::endl;
        else std::cout << key << " OFF" << std::endl;
    }
}

//bool Events_manager::get(std::string key) {
//    return control_tools[key];
//}

void Events_manager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    _camera_ptr->process_mouse_scroll(yoffset);
}

void Events_manager::mouse_callback(GLFWwindow* window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if(_firstMouse)
    {
        _lastX = xpos;
        _lastY = ypos;
        _firstMouse = false;
    }

    float xoffset = xpos - _lastX;
    float yoffset = _lastY - ypos;
    _lastX = xpos;
    _lastY = ypos;

    _camera_ptr->process_mouse_movement(xoffset, yoffset);
}
