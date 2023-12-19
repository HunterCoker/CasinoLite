#pragma once

#include "Games/Games.hpp"

#include <vector>

class GameManager {
public:
    typedef BasicGame*                  GamePointer;

    static void Init();
    static void Update();
    static void Terminate();

    static GamePointer ActiveGame() { return activeGame_; }
private:
    static void GoTo(Game game);
private:
    static GamePointer activeGame_;
};

