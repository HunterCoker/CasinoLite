#include "Input.hpp"

bool Input::KeyUp(int code) {
    auto window = glfwGetCurrentContext();
    return glfwGetKey(window, code) == GLFW_RELEASE;
}

bool Input::KeyDown(int code) {
    auto window = glfwGetCurrentContext();
    return glfwGetKey(window, code) == GLFW_PRESS;
}
