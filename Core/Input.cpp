#include "Input.hpp"

static bool downKeys[256] = { false };

void Input::SetKeyUp(SDL_Keycode code) {
    downKeys[code] = false;
}

void Input::SetKeyDown(SDL_Keycode code) {
    downKeys[code] = true;
}

bool Input::KeyUp(SDL_Keycode code) {
    return false;
}

bool Input::KeyDown(SDL_Keycode code) {
    return downKeys[code];;
}
