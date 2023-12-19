#include "GUI.hpp"

#include <iostream>

struct GUIData {
    // Account Menu
    Ref<Texture> accountMenuContainer;
    Ref<Texture> buttonTakeOutLoan;

    // Input Number Interface
    Ref<Texture> inputNumberInterfaceContainer;
    Ref<Texture> buttonSubmit;
    Ref<Texture> buttonClose;
    Ref<Texture> buttonBackspace;
    Ref<Texture> buttonNumbers[10];
};

static GUIData s_data;
static bool leftMouseButtonDownLastFrame = false;
static bool leftMouseButtonDownCurrFrame = false;
static bool s_inputNumberInterfaceOpen = false;

glm::vec2 PixelCoordinatesToNDC(double x, double y);

void GUI::Init() {
    s_data.accountMenuContainer             = Texture::Create("../Assets/Textures/GUI/GUI_AccountMenuContainer.png");
    s_data.buttonTakeOutLoan                = Texture::Create("../Assets/Textures/GUI/GUI_ButtonTakeOutLoan.png");

    s_data.inputNumberInterfaceContainer    = Texture::Create("../Assets/Textures/GUI/GUI_InputNumberInterfaceContainer.png");
    s_data.buttonClose                      = Texture::Create("../Assets/Textures/GUI/GUI_ButtonClose.png");
    s_data.buttonBackspace                  = Texture::Create("../Assets/Textures/GUI/GUI_ButtonBackspace.png");
    s_data.buttonSubmit                     = Texture::Create("../Assets/Textures/GUI/GUI_ButtonSubmit.png");
    for (size_t i = 0; i < 10; ++i)
        s_data.buttonNumbers[i]             = Texture::Create("../Assets/Textures/GUI/GUI_ButtonNumber" + std::to_string((i + 1) % 10) + ".png");
}

void GUI::Update() {
    leftMouseButtonDownLastFrame = false;

    if (Input::LeftMouseButtonDown())
        leftMouseButtonDownCurrFrame = true;
    if (Input::LeftMouseButtonReleased() && leftMouseButtonDownCurrFrame) {
        leftMouseButtonDownCurrFrame = false;
        leftMouseButtonDownLastFrame = true;
    }
}

glm::vec2 GUI::TopLeft(float padx, float pady) {
    return PixelCoordinatesToNDC(0.0, 0.0) + glm::vec2(padx, -pady);
}

bool GUI::Button(const glm::vec2& position, const glm::vec2& size, Ref<Texture>& texture) {
    const auto [x, y] = Input::GetMousePosition();
    glm::vec2 mousePos = PixelCoordinatesToNDC(x, y);

    bool cond_x = mousePos.x > position.x - (size.x * 0.5f) && mousePos.x < position.x + (size.x * 0.5f);
    bool cond_y = mousePos.y > position.y - (size.y * 0.5f) && mousePos.y < position.y + (size.y * 0.5f);
    if (cond_x && cond_y) {
        if (leftMouseButtonDownCurrFrame) {
            Renderer::DrawTexturedQuad(position, size, texture, 1.0f, { 0.5f, 0.5f, 0.5f, 1.0f });
            return false;
        }
        else {
            Renderer::DrawTexturedQuad(position, size, texture, 1.0f, { 0.75f, 0.75f, 0.75f, 1.0f });
            if (leftMouseButtonDownLastFrame)
                return true;
            return false;
        }
    }

    Renderer::DrawTexturedQuad(position, size, texture);
    return false;
}

bool GUI::Button(const glm::vec2& position, const glm::vec2& size,
                 Ref<Texture>& idle, Ref<Texture>& hovered, Ref<Texture>& pressed) {
    const auto [x, y] = Input::GetMousePosition();
    glm::vec2 mousePos = PixelCoordinatesToNDC(x, y);

    bool cond_x = mousePos.x > position.x - (size.x * 0.5f) && mousePos.x < position.x + (size.x * 0.5f);
    bool cond_y = mousePos.y > position.y - (size.y * 0.5f) && mousePos.y < position.y + (size.y * 0.5f);
    if (cond_x && cond_y) {
        if (leftMouseButtonDownCurrFrame) {
            Renderer::DrawTexturedQuad(position, size, pressed);
            return false;
        }
        else {
            Renderer::DrawTexturedQuad(position, size, hovered);
            if (leftMouseButtonDownLastFrame)
                return true;
            return false;
        }
    }

    Renderer::DrawTexturedQuad(position, size, idle);
    return false;
}

bool GUI::CircleButton(const glm::vec2& position, const float radius, Ref<Texture>& texture) {
    const auto [x, y] = Input::GetMousePosition();
    glm::vec2 mousePos = PixelCoordinatesToNDC(x, y);

    // Calculate the distance between the mouse position and the center of the circle
    float distance = glm::distance(mousePos, position);

    // Check if the distance is less than or equal to the radius
    if (distance <= radius) {
        if (leftMouseButtonDownCurrFrame) {
            Renderer::DrawTexturedQuad(position, glm::vec2(radius * 2.0f), texture, 1.0f, { 0.5f, 0.5f, 0.5f, 1.0f });
            return false;
        } else {
            Renderer::DrawTexturedQuad(position, glm::vec2(radius * 2.0f), texture, 1.0f, { 0.75f, 0.75f, 0.75f, 1.0f });
            if (leftMouseButtonDownLastFrame)
                return true;
            return false;
        }
    }

    Renderer::DrawTexturedQuad(position, glm::vec2(radius * 2.0f), texture);
    return false;
}


void GUI::AccountMenu() {
    Renderer::DrawTexturedQuad({ 0.0f, 0.0f }, { 1.5f, 1.5f }, s_data.accountMenuContainer,
                               1, { 1.0f, 1.0f, 1.0f, 0.7f});

    // take out loan button
    if (Button({ 0.0f, -0.55f }, { 1.0f, 0.25f }, s_data.buttonTakeOutLoan) && !s_inputNumberInterfaceOpen) {
        s_inputNumberInterfaceOpen = true;
    }
    if (s_inputNumberInterfaceOpen) {
        double loanAmount = InputNumberInterface();
        if (loanAmount != 0) {
            AccountManager::AddToBalance(std::abs(loanAmount));
            std::cout << "new balance: " << AccountManager::GetBalance() << std::endl;
            s_inputNumberInterfaceOpen = false;
        }
    }
}

double GUI::InputNumberInterface() {
    Renderer::DrawTexturedQuad({ 0.0f, -0.225f }, { 2.125f, 1.45f }, s_data.inputNumberInterfaceContainer);
    static bool bufferByFrame = false;
    static uint32_t amount = 0;
    static uint8_t digits = 0;

    // close button
    if (Button({ -0.87f, -0.75f }, { 0.24f, 0.24f }, s_data.buttonClose)) {
        bufferByFrame = false;
        return -1;
    }

    // backspace button
    if ((Button({  0.0f, -0.75f}, { 0.24f, 0.24f }, s_data.buttonBackspace) && bufferByFrame)
            || Input::KeyPressed(GLFW_KEY_BACKSPACE)) {
        amount = (amount >> 4);
        digits = digits > 0 ? digits - 1: 0;
    }

    // number buttons
    for (size_t i = 0; i < 10; ++i) {
        float x = (static_cast<float>(i % 3) - 1.0f) * 0.25f;
        float y = -static_cast<float>(reinterpret_cast<size_t>(i / 3)) * 0.25f;
        if (((Button({ x, y }, { 0.24f, 0.24f }, s_data.buttonNumbers[i]) && bufferByFrame)
                || Input::KeyPressed(GLFW_KEY_0 + (static_cast<int>(i) + 1) % 10))
                && digits < 8u ) {
            amount = (amount << 4) | i;
            ++digits;
        }
    }

    // display numbers
    for (uint32_t i = 0; i < digits; ++i) {
        uint8_t j = 0xf & (amount >> (i * 4));
        Renderer::DrawTexturedQuad({ -0.25f * (static_cast<float>(i) - 3.5f), 0.3f }, { 0.24f, 0.24f }, s_data.buttonNumbers[j]);
    }

    // submit loan request button
    if ((Button({ 0.25f, -0.75f }, { 0.24f, 0.24f }, s_data.buttonSubmit) && bufferByFrame)
            || Input::KeyPressed(GLFW_KEY_ENTER)) {
        auto convertAmount = [=](){
            double sum = 0.0;
            for (uint8_t i = 0; i < digits; ++i) {
                uint8_t j = 0xf & (amount >> (i * 4));
                sum += ((j + 1) % 10) * static_cast<int32_t>(glm::pow(10u, i));
            }
            return sum;
        };
        double ret = convertAmount();

        // check if user has sufficient funds
        if (ret > AccountManager::GetBalance())
            ret = -ret;

        digits = amount = 0;
        bufferByFrame = false;
        std::cout << "submitted amount: " << ret << std::endl;
        return ret;
    }

    bufferByFrame = true;
    return 0;
}

glm::vec2 PixelCoordinatesToNDC(double x, double y) {
    auto width  = static_cast<float>(Renderer::GetWindowWidth()),
         height = static_cast<float>(Renderer::GetWindowHeight());
    float w_aspect = width / height;
    return {
         (static_cast<float>(x) / width * 2.0f - 1.0f) * w_aspect,
        -(static_cast<float>(y) / height * 2.0f - 1.0f)
    };
}