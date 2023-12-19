#include "GameManager.hpp"

GameManager::GamePointer GameManager::activeGame_ = new MainMenu;

void GameManager::Init() {
    activeGame_->Init();
}

void GameManager::Update() {
    auto& state = activeGame_->GetGameState();

    if (state.shouldClose) {
        GoTo(state.nextGame);
    }
}

void GameManager::Terminate() {
    activeGame_->Terminate();
}

void GameManager::GoTo(Game game) {
    activeGame_->Terminate();
    switch (game) {
        case Game::EXIT:        std::exit(-1); // TODO (hunter): find better way to exit safely
        case Game::MAIN_MENU:   activeGame_ = new MainMenu; break;
        case Game::SLOTS:       activeGame_ = new Slots; break;
        case Game::ROULETTE:    activeGame_ = new Roulette; break;
        case Game::GO_FISH:     activeGame_ = new GoFish; break;
        case Game::BLACKJACK:   activeGame_ = new Blackjack; break;
        case Game::POKER:       activeGame_ = new Poker; break;
    }
}


