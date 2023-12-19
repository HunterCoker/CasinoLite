#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"

class Renderer {
public:
    static void Init();
    static void Update(int width, int height);
    static void Terminate();

    static int GetWindowWidth();
    static int GetWindowHeight();
    static float GetAspectRatio();

    static void BeginFrame();
    static void EndFrame();
    static void Flush();

    static void ClearColor(const glm::vec4& color);

    // Primitives
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
    static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

    static void DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture,
                                 float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawRotatedTexturedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,const Ref<Texture>& texture,
                                        float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawTexturedQuad(const glm::mat4& transform, const Ref<Texture>& texture,
                                 float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
private:
    static void StartBatch();
    static void NextBatch();
};
