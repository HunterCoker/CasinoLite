#include "VertexArray.hpp"

VertexArray::VertexArray()
    :handle_(0) {
    glGenVertexArrays(1, &handle_);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &handle_);
}

void VertexArray::AddVertexBuffer(const std::unique_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& bufferLayout) {
    glBindVertexArray(handle_);
    vertexBuffer->Bind();
    uint32_t offset = 0;
    const auto& elements = bufferLayout.getElements();
    for (std::size_t i = 0; i < elements.size(); ++i) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                              bufferLayout.getStride(), reinterpret_cast<const void*>(offset));
        offset += element.count * BufferLayoutElement::getSizeOfType(element.type);
    }
}

void VertexArray::AddElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer, GLsizeiptr size, const void* data) {
    glBindVertexArray(handle_);
    elementBuffer->BufferData(size, data);
    elementBuffer_ = elementBuffer;
}