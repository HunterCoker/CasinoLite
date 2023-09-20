#include "../Application.hpp"
#include "../../Renderer/Renderer.hpp"

#include <iostream>

void Slots::Init() {

}

void Slots::Update() {
    if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
        std::cout << "going to main menu\n";
        Application::SetActiveGame(Games::pMainMenu_g);
        return;
    }

    Renderer::ClearColor({0.0f, 0.0f, 0.0f, 1.0f});

    Renderer::BeginScene();
    /* your code goes here */


    /* ------------------- */
    Renderer::EndScene();
}

void Slots::Terminate() {

}