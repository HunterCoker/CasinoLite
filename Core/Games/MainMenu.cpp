#include "../Game.hpp"

#include "../Application.hpp"
#include "../../Renderer/Renderer.hpp"

#include <iostream>

void MainMenu::Init() {

}

void MainMenu::Update() {
    if (Input::KeyDown(SDLK_1)) {
        std::cout << "playing slots\n";
        Application::SetActiveGame(Games::pSlots_g);
        return;
    }

    Renderer::ClearColor({1.0f, 0.0f, 1.0f, 1.0f});
    Renderer::Flush();
}

void MainMenu::Terminate() {

}