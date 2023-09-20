#include "../Application.hpp"
#include "../../Renderer/Renderer.hpp"

#include <iostream>

void MainMenu::Init() {

}

void MainMenu::Update() {
    if (Input::KeyDown(GLFW_KEY_1)) {
        std::cout << "playing slots\n";
        Application::SetActiveGame(Games::pSlots_g);
        return;
    }

    Renderer::ClearColor({ 1.0, 0.0f, 1.0f, 1.0f });

    // Testing draw calls
    Renderer::BeginScene();

    float r = glm::sin(glfwGetTime());
    Renderer::DrawRotatedQuad({ r, 0.0f }, { 1.0f, 1.0f }, r * 180.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
    Renderer::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {1.0f, 1.0f, 1.0f, 1.0f});

//    auto texture = Texture::Create("../Assets/Textures/test.png");
//    Renderer::DrawTexturedQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, texture);

    Renderer::EndScene();
}

void MainMenu::Terminate() {

}