#include "../Game.hpp"

#include "../Application.hpp"
#include "../../Renderer/Renderer.hpp"

#include <iostream>

void Slots::Init() {

}

void Slots::Update() {
    if (Input::KeyDown(SDLK_ESCAPE)) {
        std::cout << "going to main menu\n";
        Application::SetActiveGame(Games::pMainMenu_g);
        return;
    }

    Renderer::ClearColor({1.0f, 1.0f, 0.0f, 1.0f});
    Renderer::Flush();
}

void Slots::Terminate() {

}