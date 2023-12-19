#include "Core/Application.hpp"

int main() {
    auto app = Application::Get();
    app->Run();
    // delete app; // figure out why this is causing a segfault

    return 0;
}
