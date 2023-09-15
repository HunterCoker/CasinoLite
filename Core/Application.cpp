#include "Application.hpp"

#include "Input.hpp"
#include "../Renderer/Renderer.hpp"

#include <iostream>

Application* Application::pInstance_s = nullptr;
SDL_Window* Application::pWindow_s = nullptr;
Game* Application::pActiveGame_s = nullptr;

Application::Application() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }

    uint32_t flags = 0;
    pWindow_s = SDL_CreateWindow("CasinoLite", 800, 500, flags);
    if (!pWindow_s) {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }
    SDL_SetWindowPosition(pWindow_s, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(pWindow_s);

    Renderer::Init();
    Games::pMainMenu_g->Init();
    Games::pSlots_g->Init();

    pActiveGame_s = Games::pMainMenu_g;
}

void Application::Run() {
    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    Input::SetKeyDown(event.key.keysym.sym);
                    break;
                case SDL_EVENT_KEY_UP:
                    Input::SetKeyUp(event.key.keysym.sym);
                    break;
                default:
                    // Unhandled Event
                    break;
            }
        }

        pActiveGame_s->Update();
    }

    Games::pMainMenu_g->Terminate();
    Games::pSlots_g->Terminate();
    SDL_DestroyWindow(pWindow_s);
    SDL_Quit();
}