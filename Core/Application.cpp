#include "Application.hpp"

#include "AccountManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "../GUI/GUI.hpp"
#include "GameManager.hpp"

#include <iostream>
#include <chrono>

double GetTime() {
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    using std::chrono::system_clock;
    auto micros_since_epoch = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    return static_cast<double>(micros_since_epoch) * 0.001;
}

struct Stats {
    double ms_per_frame = 0.0f;
    double avg_fps = 0.0f;
};

static Stats s_stats;

Application* Application::pInstance_s = nullptr;

Application::Application() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "gladLoadGLLoader error: could not load OpenGL" << std::endl;
        std::exit(-1);
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    AccountManager::Init();

    // Generates vertex buffers and shaders needed to draw primitives
    Renderer::Init();

    // initializes all of the assets needed for GUI components
    GUI::Init();

    // Initializes the main menu
    GameManager::Init();
}

void Application::Run() {
    float ts = 0;
    double start = GetTime(), end = 0;

    while (!window_.ShouldClose()) {
        window_.Update();

        end = GetTime();
        s_stats.ms_per_frame = end - start;
        ts = static_cast<float>(s_stats.ms_per_frame);
        start = end;

        // calculate performance stats
        static double timer = 1000.0, ts_acc = 0.0;
        static uint32_t frame_count = 0;
        if ((timer -= s_stats.ms_per_frame) <= 0.0f) {
            s_stats.avg_fps = 1000.0 / (ts_acc / frame_count);
            timer = 1000.0;
            ts_acc = frame_count = 0;
            // std::cout << s_stats.avg_fps << " frames/sec" << '\n';
        }
        ts_acc += ts;
        ++frame_count;

        Renderer::Update(window_.GetWidth(), window_.GetHeight());
        GUI::Update();
        GameManager::Update();

        auto game = GameManager::ActiveGame();
        game->Update(ts * 0.001f);

    }

    AccountManager::Terminate();

    // flushes all buffers and frees all allocated memory
    Renderer::Terminate();

    // closes game safely
    GameManager::Terminate();

}

