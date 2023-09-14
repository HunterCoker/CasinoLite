#include "../Game.hpp"

void MainMenu::Init() {

}

void MainMenu::Update() {
    auto window = Applation::GetWindow();
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        Application::SetActiveGame(Games::pSlots_g);
    }
}

void MainMenu::Terminate() {

}