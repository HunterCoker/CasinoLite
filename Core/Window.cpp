#include "Window.hpp"

#include <iostream>

static void glfw_error_callback(int error, const char* description);
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

Window::Window()
    : width_(800), height_(500) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) exit(-1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width_, height_, "CasinoLite", nullptr, nullptr);
    if (!window_) exit(-1);
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebuffer_resize_callback);
    glfwSetWindowSizeLimits(window_, 800, 500, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSwapInterval(1);
}

Window::~Window() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Window::Update() {
    glfwPollEvents();
    glfwSwapBuffers(window_);
    glfwGetWindowSize(window_, &width_, &height_);
}

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}