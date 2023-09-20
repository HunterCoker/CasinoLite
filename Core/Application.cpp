#include "Application.hpp"

#include "Input.hpp"
#include "../Renderer/Renderer.hpp"

#include <iostream>

static void glfw_error_callback(int error, const char* description);
static void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

Application* Application::pInstance_s = nullptr;
GLFWwindow* Application::pWindow_s = nullptr;
Game* Application::pActiveGame_s = nullptr;

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow_s = glfwCreateWindow(800, 500, "CasinoLite", nullptr, nullptr);
    if (!pWindow_s) {
        std::cerr << "glfwCreateWindow error: could not create window" << std::endl;
        std::exit(-1);
    }
    glfwMakeContextCurrent(pWindow_s);
    glfwSetFramebufferSizeCallback(pWindow_s, framebuffer_resize_callback);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader error: could not load OpenGL" << std::endl;
        std::exit(-1);
    }

    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer::Init();
    Games::pMainMenu_g->Init();
    Games::pSlots_g->Init();

    pActiveGame_s = Games::pMainMenu_g;
}

void Application::Run() {

    while (!glfwWindowShouldClose(pWindow_s)) {
        glfwPollEvents();
        glfwSwapBuffers(pWindow_s);

        pActiveGame_s->Update();
    }

    Games::pMainMenu_g->Terminate();
    Games::pSlots_g->Terminate();
    glfwDestroyWindow(pWindow_s);
    glfwTerminate();
}


static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}