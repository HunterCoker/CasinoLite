#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"

class Application {
public:
    Application(const Application&) = delete;
    ~Application() = default;

    static Application* Get() {
        if (!pInstance_s)
            pInstance_s = new Application();
        return pInstance_s;
    }

    static void Run();

    static const GLFWwindow* GetWindow() { return pWindow_s; };
    static void SetActiveGame(Game* game) { pActiveGame_s = game; }
private:
    static GLFWwindow* pWindow_s;
    static Game* pActiveGame_s;
private:
    Application();
    static Application* pInstance_s;
};
