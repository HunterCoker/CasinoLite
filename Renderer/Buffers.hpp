#pragma once

#include <glad/glad.h>

#include <vector>

struct BufferLayoutElement {
    GLint count;
    GLenum type;
    GLboolean normalized;

    static uint32_t getSizeOfType(GLenum type) {
        switch (type) {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:   return 4;
            default:                return 0;
        }
    }
};

class BufferLayout {
public:
    BufferLayout()
        :stride_(0) {
    }
    BufferLayout(const BufferLayout&) = delete;
    ~BufferLayout() = default;

    GLsizei getStride() const { return stride_; }
    const std::vector<BufferLayoutElement>& getElements() const { return elements_; }

    void PushFloat(int32_t count) {
        elements_.push_back({ count, GL_FLOAT, GL_FALSE });
        stride_ += count * BufferLayoutElement::getSizeOfType(GL_FLOAT);
    }

    void PushUInt(int32_t count) {
        elements_.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
        stride_ += count * BufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT);
    }
private:
    std::vector<BufferLayoutElement> elements_;
    GLsizei stride_;
};

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const VertexBuffer&) = delete;
    ~VertexBuffer();

    void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, handle_); }
    void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    void BufferData(GLsizeiptr size, const void* data) const;
    void BufferSubdata(GLintptr offset, GLsizeiptr size, const void* data);
private:
    GLuint handle_;
};

class ElementBuffer {
public:
    ElementBuffer();
    ElementBuffer(const ElementBuffer&) = delete;
    ~ElementBuffer();

    void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_); }
    void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    GLsizei GetCount() const { return count_; }

    void BufferData(GLsizeiptr size, const void* data);
private:
    GLuint handle_{};
    GLsizei count_;
};

