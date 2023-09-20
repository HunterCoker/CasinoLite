#include "Buffers.hpp"

VertexBuffer::VertexBuffer()
    :handle_(0) {
    glGenBuffers(1, &handle_);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &handle_);
}

void VertexBuffer::BufferData(GLsizeiptr size, const void *data) const {
    glBindBuffer(GL_ARRAY_BUFFER, handle_);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VertexBuffer::BufferSubdata(GLintptr offset, GLsizeiptr size, const void *data) {
    glBindBuffer(GL_ARRAY_BUFFER, handle_);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

ElementBuffer::ElementBuffer()
    :handle_(0), count_(0) {
    glGenBuffers(1, &handle_);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &handle_);
}

void ElementBuffer::BufferData(GLsizeiptr size, const void *data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    count_ = size / sizeof(uint32_t);
}
