#include "Renderer.hpp"

#include <iostream>

SDL_Renderer* Renderer::pRenderer_s = nullptr;

void Renderer::Init() {
    auto window = Application::GetWindow();
    pRenderer_s = SDL_CreateRenderer(const_cast<SDL_Window*>(window), nullptr, SDL_RENDERER_ACCELERATED);
    if (pRenderer_s == nullptr) {
        std::cout << "SDL_SetRenderDrawColor error: " << SDL_GetError() << std::endl;
        std::exit(-1);
    }
}

void Renderer::Flush() {
    SDL_RenderPresent(pRenderer_s);
}

void Renderer::ClearColor(const glm::vec4& color) {
    auto r = static_cast<uint8_t>(color.r * 0xff);
    auto g = static_cast<uint8_t>(color.g * 0xff);
    auto b = static_cast<uint8_t>(color.b * 0xff);
    auto a = static_cast<uint8_t>(color.a * 0xff);
    SDL_SetRenderDrawColor(pRenderer_s, r, g, b, a);
    SDL_RenderClear(pRenderer_s);
}
