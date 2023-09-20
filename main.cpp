#include "Core/Application.hpp"

int main() {
    auto app = Application::Get();
    app->Run();
    delete app;

    return 0;
}
