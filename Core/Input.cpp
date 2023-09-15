#include "Input.hpp"

#include <vector>
#include <algorithm>

static std::vector<SDL_Keycode> keysDown(104);
static std::vector<SDL_Keycode> keysUp(104);

void Input::SetKeyUp(SDL_Keycode code) {
    for (int i = 0; i < keysDown.size(); ++i) {
        if (keysDown[i] == code)
            keysDown.erase(keysDown.begin() + i);
    }
}

void Input::SetKeyDown(SDL_Keycode code) {
    if (std::none_of(keysDown.begin(), keysDown.end(), [=](SDL_Keycode keycode) {
        return keycode == code;
    })) {
        keysDown.push_back(code);
    }
}

bool Input::KeyUp(SDL_Keycode code) {
    return false;
}

bool Input::KeyDown(SDL_Keycode code) {
    return std::any_of(keysDown.begin(), keysDown.end(), [=](SDL_Keycode keycode) {
        return keycode == code;
    });
}
