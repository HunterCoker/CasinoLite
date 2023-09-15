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

    double r = (glm::sin((float)SDL_GetTicks() / 1000.0f) + 1.0f) / 2.0f;
    Renderer::ClearColor({ r, 0.0f, 1.0f, 1.0f });
    Renderer::Flush();
}

void MainMenu::Terminate() {

}