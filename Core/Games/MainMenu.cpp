#include "Games.hpp"

#include "../../GUI/GUI.hpp"

#include <iostream>

static Ref<Texture> s_textures[11];
static bool s_initializedTextures = false;
static bool s_accountMenuOpen = false;

void MainMenu::Init() {
    if (s_initializedTextures)
        return;

    s_textures[0]  = Texture::Create("../Assets/Textures/MainMenu_Background.png");
    s_textures[1]  = Texture::Create("../Assets/Textures/MainMenu_TitleSplash.png");
    s_textures[2]  = Texture::Create("../Assets/Textures/MainMenu_TitleSpashBackground.png");
    s_textures[3]  = Texture::Create("../Assets/Textures/MainMenu_ButtonAccountMenuIdle.png");
    s_textures[4]  = Texture::Create("../Assets/Textures/MainMenu_ButtonAccountMenuHovered.png");
    s_textures[5]  = Texture::Create("../Assets/Textures/MainMenu_ButtonAccountMenuPressed.png");
    s_textures[6]  = Texture::Create("../Assets/Textures/MainMenu_ButtonSlots.png");
    s_textures[7]  = Texture::Create("../Assets/Textures/MainMenu_ButtonRoulette.png");
    s_textures[8]  = Texture::Create("../Assets/Textures/MainMenu_ButtonGoFish.png");
    s_textures[9]  = Texture::Create("../Assets/Textures/MainMenu_ButtonBlackjack.png");
    s_textures[10] = Texture::Create("../Assets/Textures/MainMenu_ButtonPoker.png");
    s_initializedTextures = true;
}

void MainMenu::Update(float ts) {
    if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
        s_accountMenuOpen = false;
    }

    /* ----------- Setup ----------- */

    int width = Renderer::GetWindowWidth();
    int height = Renderer::GetWindowHeight();
    static float acc_ts = 0.0f;
    acc_ts += ts;

    /* ------- Renderer DEMO ------- */

    // Clear the screen with any color to make sure you're rendering on a clean canvas
    Renderer::ClearColor({ 0.0f, 0.1f, 0.0f, 1.0f });

    // Before trying to draw anything, begin the render frame...
    Renderer::BeginFrame();

    // Shimmering background effect
    // GUI::ShaderSurface(../Assets/Shaders/MainMenu_Surface.glsl)

    // Scrolling background effect
    auto factor = [](float v) {
        return (v * v) * 0.045f + 1.0f;
    };
    float xn = 6 * factor(static_cast<float>(width) / height);
    float speed = 0.25f; // must be any number equal to 1/2^n
    static float scroll_acc = 0.0f;
    scroll_acc = scroll_acc < 2.0f ? scroll_acc + ts : 0.0f;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < xn; ++x) {
            float x_offset = y % 2 == 0 ? 0.0f : 0.5f;
            glm::vec2 position{ static_cast<float>(x) - xn / 2.0f + x_offset,
                               (static_cast<float>(y) - 2.0f) * 0.5f };
            glm::vec2 scroll_offset(-scroll_acc * speed);
            Renderer::DrawTexturedQuad(position + scroll_offset, { 1.0f, 1.0f }, s_textures[0]);
        }
    }

    // Title graphic & effects
    Renderer::DrawRotatedTexturedQuad({ 0.0f, 0.1f }, { 2.0f, 2.0f }, acc_ts * 45.0f, s_textures[2],
                                      2.0f, { 0.65f, 0.65f, 0.4f, 0.1f });
    Renderer::DrawRotatedTexturedQuad({ 0.0f, 0.1f }, { 2.5f, 2.5f }, acc_ts * 30.0f, s_textures[2],
                                      1.0f, { 0.65f, 0.65f, 0.4f, 0.1f });
    Renderer::DrawTexturedQuad({ 0.0f, 0.25f }, { 1.537f, 0.99f }, s_textures[1]);

    // Interactive UI
    // * Games selection buttons
    if (GUI::Button({ -1.0f, -0.45f }, { 0.45f, 0.25f }, s_textures[6]) && !s_accountMenuOpen) {
        this->state_.nextGame = Game::SLOTS;
        this->Close();
        return;
    }
    if (GUI::Button({ -0.5f, -0.45f }, { 0.45f, 0.25f }, s_textures[7]) && !s_accountMenuOpen) {
        this->state_.nextGame = Game::ROULETTE;
        this->Close();
        return;
    }
    if (GUI::Button({  0.0f, -0.45f }, { 0.45f, 0.25f }, s_textures[8]) && !s_accountMenuOpen) {
        this->state_.nextGame = Game::GO_FISH;
        this->Close();
        return;
    }
    if (GUI::Button({  0.5f, -0.45f }, { 0.45f, 0.25f }, s_textures[9]) && !s_accountMenuOpen) {
        this->state_.nextGame = Game::BLACKJACK;
        this->Close();
        return;
    }
    if (GUI::Button({  1.0f, -0.45f }, { 0.45f, 0.25f }, s_textures[10]) && !s_accountMenuOpen) {
        this->state_.nextGame = Game::POKER;
        this->Close();
        return;
    }
    // * Account button & interface
    if (s_accountMenuOpen) {
        Renderer::DrawQuad({ 0.0f, 0.0f }, { width, height }, { 0.0f, 0.0f, 0.0f, 0.25f });
        GUI::AccountMenu();
    }
    if (GUI::Button(GUI::TopLeft(0.25f, 0.25f), { 0.25f, 0.25f }, s_textures[3], s_textures[4], s_textures[5])) {
        s_accountMenuOpen = !s_accountMenuOpen;

        if (s_accountMenuOpen)
            AccountManager::PrintInfo();
    }

    // You must end the render frame to draw everything to the screen
    Renderer::EndFrame();
}

void MainMenu::Terminate() {


    delete this;
}
