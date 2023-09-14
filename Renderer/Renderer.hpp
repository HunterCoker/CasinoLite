#pragma once

#include "../Core/Application.hpp"

#include <glm/glm.hpp>

class Renderer {
public:
    static void Init();
    static void Flush();

    static void ClearColor(const glm::vec4& color);

    // static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    // static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    // static void DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    // static void DrawRotatedTexturedQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

private:
    static SDL_Renderer* pRenderer_s;
};
