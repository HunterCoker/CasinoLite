#pragma once

#include "Window.hpp"

class Application {
public:
    Application(const Application&) = delete;
    ~Application() = default;

    static Application* Get() {
        if (!pInstance_s)
            pInstance_s = new Application();
        return pInstance_s;
    }

    void Run();
private:
    Window window_;
private:
    Application();
    static Application* pInstance_s;
};
