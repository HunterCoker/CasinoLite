#pragma once

#include <SDL.h>

#include "Game.hpp"

class Application {
public:
    Application(const Application&) = delete;
    ~Application() = default;

    static Application* Get() {
        if (!pInstance_s) {
            pInstance_s = new Application();
        }
        return pInstance_s;
    }

    static const SDL_Window* GetWindow() { return pWindow_s; };
    static void SetActiveGame(Game* game) { pActiveGame_s = game; }

    void Run();
private:
    static SDL_Window* pWindow_s;
    static Game* pActiveGame_s;
private:
    Application();
    static Application* pInstance_s;
};
