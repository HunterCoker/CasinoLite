#include "Input.hpp"

bool Input::KeyUp(int code) {
    auto window = glfwGetCurrentContext();
    return glfwGetKey(window, code) == GLFW_RELEASE;
}

bool Input::KeyDown(int code) {
    auto window = glfwGetCurrentContext();
    return glfwGetKey(window, code) == GLFW_PRESS;
}

std::tuple<double, double> Input::GetMousePosition() {
    auto window = glfwGetCurrentContext();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { x, y };
}

bool Input::LeftMouseButtonDown() {
    auto window = glfwGetCurrentContext();
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Input::LeftMouseButtonReleased() {
    auto window = glfwGetCurrentContext();
    return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE;
}

bool Input::KeyPressed(int code) {
    static bool keysPressedLastFrame[GLFW_KEY_LAST] = { };
    bool ret = false;
    if (KeyDown(code)) {
        ret = !keysPressedLastFrame[code];
        keysPressedLastFrame[code] = true;
    }
    else {
        keysPressedLastFrame[code] = false;
    }
    return ret;
}


