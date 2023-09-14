#include "Application.hpp"

Application* Application::pInstance_s = nullptr;
Game* Application::pActiveGame_s = nullptr;

Application::Application() {
    Games::pMainMenu_g->Init();
    Games::pSlots_g->Init();

    pActiveGame_s = Games::pMainMenu_g;
}

void Application::Run() {

    bool running = true;
    while (running) {


        if (!pActiveGame_s) {
            pActiveGame_s = Games::pMainMenu_g;
        }

        pActiveGame_s->Update();
    }

    Games::pMainMenu_g->Terminate();
    Games::pSlots_g->Terminate();
}
