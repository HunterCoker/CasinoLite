#pragma once

#include <GLFW/glfw3.h>

#include <tuple>

class Input {
public:
    // Keyboard events
    static bool KeyUp(int code);
    static bool KeyDown(int code);
    static bool KeyPressed(int code);

    // Mouse events
    static std::tuple<double, double> GetMousePosition();
    static bool LeftMouseButtonDown();
    static bool LeftMouseButtonReleased();
};
