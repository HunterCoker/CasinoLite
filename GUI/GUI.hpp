#pragma once

#include <glm/glm.hpp>

#include "../Core/AccountManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Core/Input.hpp"

#include <string>

class GUI {
public:
    static void Init();
    static void Update();

    static glm::vec2 TopLeft(float padx, float pady);

    static bool Button(const glm::vec2& position, const glm::vec2& size, Ref<Texture>& texture);
    static bool Button(const glm::vec2& position, const glm::vec2& size,
                       Ref<Texture>& idle, Ref<Texture>& hovered, Ref<Texture>& pressed);
    static bool CircleButton(const glm::vec2& position, float radius, Ref<Texture>& texture);

    static void AccountMenu();
    static double InputNumberInterface();
private:

};