#pragma once

#include <SDL.h>

class Input {
public:
    static void SetKeyUp(SDL_Keycode code);
    static void SetKeyDown(SDL_Keycode code);

    static bool KeyUp(SDL_Keycode code);
    static bool KeyDown(SDL_Keycode code);
};
