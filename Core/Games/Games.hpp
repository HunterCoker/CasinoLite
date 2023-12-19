#include "../BasicGame.hpp"
#include "../Deck.h"

class MainMenu : public BasicGame {
public:
    MainMenu() : BasicGame("Main Menu") { };
    MainMenu(const MainMenu&) = default;
    ~MainMenu() = default;

    void Init() override;
    void Update(float ts) override;
    void Terminate() override;
private:
};

class Slots : public BasicGame {
public:
    Slots() : BasicGame("Slots") { };
    Slots(const Slots&) = default;
    ~Slots() = default;

    void Init() override;
    void Update(float ts) override;
    void Terminate() override;
private:
};

class Roulette : public BasicGame {
public:
    Roulette() : BasicGame("Roulette") { };
    Roulette(const Roulette&) = default;
    ~Roulette() = default;

    void Init() override;
    void Update(float ts) override;
    void Terminate() override;
private:
};

class GoFish : public BasicGame {
public:
    GoFish() : BasicGame("Go Fish") { };
    GoFish(const GoFish&) = default;
    ~GoFish() = default;

    void Init() override;
    void Update(float ts) override;
    void Terminate() override;
private:
};

class Blackjack : public BasicGame {
public:
    Blackjack() : BasicGame("Blackjack") { };
    Blackjack(const Blackjack&) = default;
    ~Blackjack() = default;

    void Init() override;
    void Update(float ts) override;
    void Terminate() override;

private:
    static int wager;
    static bool BJTie;
    static bool BJLose;
    static bool BJWin;
    static Ref<Texture> aiHandTextures[11];
    static int aiHandValues[11];
    static int handValues[11];
    static Ref<Texture> handTextures[11];
    static Ref<Texture> BJtextures[12];
    static int blackJack_initialized;
    static bool player_stand[0];
    static int getScore(int (&hand)[11]);
    static void runAI();
    static Deck blackJackDeck;
};

class Poker : public BasicGame {
public:
    Poker() : BasicGame("Poker") { };
    Poker(const Poker&) = default;
    ~Poker() = default;

    void Init() override;
    void Update(float ts) override;
    void Terminate() override;
private:
};