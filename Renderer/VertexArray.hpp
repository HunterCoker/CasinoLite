#pragma once

#include "Buffers.hpp"

#include <memory>

class VertexArray {
public:
    VertexArray();
    VertexArray(const VertexArray&) = delete;
    ~VertexArray();

    void Bind() const { glBindVertexArray(handle_); }
    void Unbind() const { glBindVertexArray(0); }

    void AddVertexBuffer(const std::unique_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& bufferLayout);
    void AddElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer,  GLsizeiptr size, const void* data);

    const std::shared_ptr<ElementBuffer>& GetElementBuffer() const { return elementBuffer_; }
private:
    std::shared_ptr<ElementBuffer> elementBuffer_;
    GLuint handle_;
};
