#pragma once

#include "Input.hpp"

#include <utility>
#include <string>
#include <memory>

class Game {
public:
    explicit Game(std::string title = "Game")
        :title_(std::move(title)) {

    }
    Game(const Game&) = default;
    ~Game() = default;

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Terminate() = 0;
private:
    std::string title_;
};

class MainMenu : public Game {
public:
    MainMenu() : Game("Main Menu") { };
    MainMenu(const MainMenu&) = default;
    ~MainMenu() = default;

    void Init() override;
    void Update() override;
    void Terminate() override;
private:
};

class Slots : public Game {
public:
    Slots() : Game("Slots") { };
    Slots(const Slots&) = default;
    ~Slots() = default;

    void Init() override;
    void Update() override;
    void Terminate() override;
private:
};

namespace Games {
    inline MainMenu* pMainMenu_g = new MainMenu();
    inline Slots* pSlots_g = new Slots();
}