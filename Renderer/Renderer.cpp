#include "Renderer.hpp"

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffers.hpp"
#include "Primitive.hpp"

#include <iostream>
#include <vector>
#include <array>

struct RendererData {
    float aspect = 0.0f;
    int width = 0, height = 0;

    // Primitives
    static const uint32_t MaxQuads = 10000;
    static const uint32_t MaxTextureSlots = 16;

    std::unique_ptr<VertexArray> quadVertexArray;
    std::unique_ptr<VertexBuffer> quadVertexBuffer;
    Ref<Shader> quadShader;

    GLsizei quadIndexCount = 0;
    QuadVertex* quadVertexBufferBase = nullptr;
    QuadVertex* quadVertexBufferPtr = nullptr;

    GLsizei textureSlotIndex = 0;
    std::array<Ref<Texture>, MaxTextureSlots> textureSlots;

    glm::vec4 quadVertexPositions[4] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f, -0.5f, 0.0f, 1.0f },
        {  0.5f,  0.5f, 0.0f, 1.0f },
        { -0.5f,  0.5f, 0.0f, 1.0f }
    };

};

static RendererData data_s;

void Renderer::Init() {
    data_s.quadShader = Shader::Create("../Assets/Shaders/vertex.glsl", "../Assets/Shaders/fragment.glsl");
    data_s.quadShader->Bind();
    int32_t samplers[RendererData::MaxTextureSlots];
    for (int32_t i = 0; i < RendererData::MaxTextureSlots; ++i)
        samplers[i] = i;
    data_s.quadShader->SetUniformIntArray("u_Textures", RendererData::MaxTextureSlots, samplers);
    data_s.textureSlots[0] = Texture::Create("../Assets/Textures/white.png");

    data_s.quadVertexArray = std::make_unique<VertexArray>();
    data_s.quadVertexBuffer = std::make_unique<VertexBuffer>();
    BufferLayout quadBufferLayout;
    quadBufferLayout.PushFloat(3); // position
    quadBufferLayout.PushFloat(4); // color
    quadBufferLayout.PushFloat(2); // texCoord
    quadBufferLayout.PushFloat(1); // texIndex
    quadBufferLayout.PushFloat(1); // tilingFactor
    data_s.quadVertexArray->AddVertexBuffer(data_s.quadVertexBuffer, quadBufferLayout);

    auto quadElementBuffer = std::make_shared<ElementBuffer>();
    uint32_t indices[RendererData::MaxQuads * 6];
    uint32_t offset = 0;
    for (std::size_t i = 0; i < RendererData::MaxQuads * 6; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;
        offset += 4;
    }
    data_s.quadVertexArray->AddElementBuffer(quadElementBuffer, static_cast<GLsizeiptr>(sizeof(indices)), indices);

    data_s.quadVertexBufferBase = new QuadVertex[RendererData::MaxQuads * 4];
    data_s.quadVertexBufferPtr = data_s.quadVertexBufferPtr;
}

void Renderer::Update(int width, int height) {
    data_s.width = width;
    data_s.height = height;
    data_s.aspect = static_cast<float>(height) / width;
}

void Renderer::Terminate() {

}

int Renderer::GetWindowWidth() {
    return data_s.width;
}

int Renderer::GetWindowHeight() {
    return data_s.height;
}

float Renderer::GetAspectRatio() {
    return data_s.aspect;
}

void Renderer::BeginFrame() {
    StartBatch();
}

void Renderer::EndFrame() {
    Flush();
}

void Renderer::Flush() {
    if (data_s.quadIndexCount) {
        data_s.quadVertexArray->Bind();

        auto dataSize = (uint32_t)((uint8_t*)data_s.quadVertexBufferPtr - (uint8_t*)data_s.quadVertexBufferBase);
        data_s.quadVertexBuffer->BufferData(dataSize, data_s.quadVertexBufferBase);

        for (uint32_t i = 0; i < data_s.textureSlotIndex; i++)
            data_s.textureSlots[i]->Bind(i);

        data_s.quadShader->Bind();
        data_s.quadShader->SetUniformFloat("u_Aspect", data_s.aspect);
        glDrawElements(GL_TRIANGLES, data_s.quadIndexCount, GL_UNSIGNED_INT, nullptr);
    }
}

void Renderer::StartBatch() {
    data_s.quadIndexCount = 0;
    data_s.quadVertexBufferPtr = data_s.quadVertexBufferBase;

    // Other primitives
    // ...

    data_s.textureSlotIndex = 1;
}


void Renderer::NextBatch() {
    Flush();
    StartBatch();
}

void Renderer::ClearColor(const glm::vec4& color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, color.a);
}

// Quads
void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.0f});
    DrawQuad(transform, color);
}

void Renderer::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
                          * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                          * glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f});
    DrawQuad(transform, color);
}

void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
    constexpr size_t quadVertexCount = 4;
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    const float textureIndex = 0.0f; // White Texture
    const float tilingFactor = 1.0f;

    if (data_s.quadIndexCount >= RendererData::MaxQuads * 6) {
        std::cerr << "error: maximum amount of quads exceeded!\n";
        return;
    }

    for (size_t i = 0; i < quadVertexCount; i++) {
        data_s.quadVertexBufferPtr->position = transform * data_s.quadVertexPositions[i];
        data_s.quadVertexBufferPtr->color = color;
        data_s.quadVertexBufferPtr->texCoord = textureCoords[i];
        data_s.quadVertexBufferPtr->texIndex = textureIndex;
        data_s.quadVertexBufferPtr->tilingFactor = tilingFactor;
        data_s.quadVertexBufferPtr++;
    }

    data_s.quadIndexCount += 6;
}

// Textured Quads
void Renderer::DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture,
                          float tilingFactor, const glm::vec4 &tintColor) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.0f});
    DrawTexturedQuad(transform, texture, tilingFactor, tintColor);
}


void Renderer::DrawRotatedTexturedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture>& texture,
                                 float tilingFactor, const glm::vec4& tintColor) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
                          * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                          * glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f});
    DrawTexturedQuad(transform, texture, tilingFactor, tintColor);
}

void Renderer::DrawTexturedQuad(const glm::mat4& transform, const Ref<Texture>& texture,
                           float tilingFactor, const glm::vec4& tintColor) {
    constexpr size_t quadVertexCount = 4;
    constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

    if (data_s.quadIndexCount >= RendererData::MaxQuads * 6) {
        std::cerr << "error: maximum amount of quads exceeded!\n";
        return;
    }

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < data_s.textureSlotIndex; ++i) {
        if (*data_s.textureSlots[i] == *texture) {
            textureIndex = (float)i;
            break;
        }
    }
    if (textureIndex == 0.0f) {
        if (data_s.textureSlotIndex >= RendererData::MaxTextureSlots)
            NextBatch();

        textureIndex = static_cast<float>(data_s.textureSlotIndex);
        data_s.textureSlots[data_s.textureSlotIndex++] = texture;
    }

    for (size_t i = 0; i < quadVertexCount; i++) {
        data_s.quadVertexBufferPtr->position = transform * data_s.quadVertexPositions[i];
        data_s.quadVertexBufferPtr->color = tintColor;
        data_s.quadVertexBufferPtr->texCoord = textureCoords[i];
        data_s.quadVertexBufferPtr->texIndex = textureIndex;
        data_s.quadVertexBufferPtr->tilingFactor = tilingFactor;
        data_s.quadVertexBufferPtr++;
    }

    data_s.quadIndexCount += 6;
}
