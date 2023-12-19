#include "Games.hpp"

#include "../../GUI/GUI.hpp"

void GoFish::Init() {

}

void GoFish::Update(float ts) {
    if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
        this->Close();
        return;
    }

    Renderer::ClearColor({ 0.0f, 0.0f, 1.0f, 1.0f });

    Renderer::BeginFrame();
    /* your code goes here */


    /* ------------------- */
    Renderer::EndFrame();
}

void GoFish::Terminate() {


    delete this;
}