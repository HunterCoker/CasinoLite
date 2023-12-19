#include "Games.hpp"
#include "../Deck.h"
#include <algorithm>
#include <ctime>

using namespace std;

bool Blackjack::player_stand[0];
int Blackjack::blackJack_initialized = false;
Ref<Texture> Blackjack::BJtextures[12];
Ref<Texture> Blackjack::handTextures[11]; //max hand size in 21 is 11: 1+1+1+1+2+2+2+2+3+3+3=21
int Blackjack::handValues[11];
int Blackjack::aiHandValues[11];
Ref<Texture> Blackjack::aiHandTextures[11];
bool Blackjack::BJWin;
bool Blackjack::BJLose;
bool Blackjack::BJTie;
int Blackjack::wager;

Deck Blackjack::blackJackDeck;

static bool s_inputInterfaceOpen = false;

void Blackjack::Init() {


    srand(time(nullptr));
    wager = -1;
    player_stand[0] = false;
    player_stand[1] = false;
    blackJackDeck.Init();
    //if(!BJtextures[0]){
        BJtextures[0] = Texture::Create("../Assets/Textures/blackjack/blackjack_wager.png");
        BJtextures[1] = Texture::Create("../Assets/Textures/chips/1_chip.png");
        BJtextures[2] = Texture::Create("../Assets/Textures/chips/5_chip.png");
        BJtextures[3] = Texture::Create("../Assets/Textures/chips/10_chip.png");
        BJtextures[4] = Texture::Create("../Assets/Textures/rouletteTable/winner.png");
        BJtextures[5] = Texture::Create("../Assets/Textures/rouletteTable/lose.png");
        BJtextures[6] = Texture::Create("../Assets/Textures/blackjack/hit.png");
        BJtextures[7] = Texture::Create("../Assets/Textures/blackjack/stand.png");
        BJtextures[8] = Texture::Create("../Assets/Textures/blackjack/tie.png");
        BJtextures[9] = Texture::Create("../Assets/Textures/rouletteTable/return.png");
        BJtextures[10] = Texture::Create("../Assets/Textures/rouletteTable/playAgain.png");
        BJtextures[11] = Texture::Create("../Assets/Textures/blackjack/oppStand.png");
    //}

    for (int &handValue: handValues) {
        handValue = 0;
    }

    for (Ref<Texture> &texture: handTextures) {
        texture = nullptr;
    }

    for (int &aiHandValue: aiHandValues) {
        aiHandValue = 0;
    }

    for (Ref<Texture> &texture: aiHandTextures) {
        texture = nullptr;
    }

    BJWin = false;
    BJLose = false;
    BJTie = false;

    //Begin game with 2 cards each:
    for(int i = 0; i < 2; i++){
        int random_integer = -1;
        int lowest = 1, highest = 52;
        //player draw
        do {
            random_integer = lowest + rand() % ((highest - lowest) + 1);
        } while (blackJackDeck.cardDrawn[random_integer]);
        handTextures[i] = blackJackDeck.cardTextures[random_integer];
        handValues[i] = blackJackDeck.cardValues[random_integer];
        blackJackDeck.cardDrawn[random_integer] = true;
        //ai draw
        do {
            random_integer = lowest + rand() % ((highest - lowest) + 1);
        } while (blackJackDeck.cardDrawn[random_integer]);
        aiHandTextures[i] = blackJackDeck.cardTextures[random_integer];
        aiHandValues[i] = blackJackDeck.cardValues[random_integer];
        blackJackDeck.cardDrawn[random_integer] = true;
    }


}

int Blackjack::getScore(int (&hand)[11]) {
    int scoreA = 0;
    for (int i: hand) {
        if (i > 10)
            scoreA += 10;
        else
            scoreA += i;
    }
    int scoreB = 0;
    for (int i: hand) {
        if (i != 1)
            if (i > 10)
                scoreB += 10;
            else
                scoreB += i;
        else
            scoreB += 11;
    }
    if (scoreA > 21)
        return scoreB;
    else if (scoreB > 21)
        return scoreA;
    else if (scoreB > scoreA)
        return scoreB;
    else
        return scoreA;
}

int ScoreCheck(int (&hand)[11]) {
    int scoreA = 0;
    for (int i: hand) {
        if (i > 10)
            scoreA += 10;
        else
            scoreA += i;
    }
    int scoreB = 0;
    for (int i: hand) {
        if (i != 1)
            if (i > 10)
                scoreB += 10;
            else
                scoreB += i;
        else
            scoreB += 11;
    }
    if (scoreA > 21 && scoreB > 20) {
        return -1;
    } else if (scoreA == 21 || scoreB == 21) {
        return 0;
    } else {
        return 1;
    }
}

void Blackjack::runAI() {
    if (getScore(aiHandValues) < 17) {
        for (int i = 0; i < 11; i++) {
            if (!aiHandTextures[i]) {
                int random_integer = -1;
                int lowest = 1, highest = 52;
                do {
                    random_integer = lowest + rand() % ((highest - lowest) + 1);
                } while (blackJackDeck.cardDrawn[random_integer]);
                aiHandTextures[i] = blackJackDeck.cardTextures[random_integer];
                aiHandValues[i] = blackJackDeck.cardValues[random_integer];
                blackJackDeck.cardDrawn[random_integer] = true;
                break;
            }
        }

    } else {
        player_stand[1] = true;
    }
}

void Blackjack::Update(float ts) {
    if (!blackJack_initialized) {
        Init();
        blackJack_initialized = true;
    }
    if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
        this->Close();
        return;
    }

    //BEFORE DRAWING CHECK IF GAME IS STILL RUNNING
    if(ScoreCheck(handValues) == 1) { //player hand under 21
        if(ScoreCheck(aiHandValues) == 0){ //ai hand = 21
            BJLose = true;
        }else if(ScoreCheck(aiHandValues) == -1) {//ai hand over 21
            BJWin = true;
        }//if neither, game continues
    }else if(ScoreCheck(handValues) == -1){ //player hand over 21
        if(ScoreCheck(aiHandValues) == 0 || ScoreCheck(aiHandValues) == 1){
            BJLose = true;
        }else{ //ai also lost
            BJTie = true;
        }
    }else if(ScoreCheck(handValues) == 0){
        if(ScoreCheck(aiHandValues) == 0){
            BJTie = true;
        }else{
            BJWin = true;
        }
    }else if(player_stand[0] && player_stand[1]){
        if(getScore(handValues) > getScore(aiHandValues)){
            BJWin = true;
        }else if(getScore(handValues) < getScore(aiHandValues)){
            BJLose = true;
        }else{
            BJTie = true;
        }
    }


    Renderer::ClearColor({0.0f, 0.2f, 0.0f, 1.0f});

    Renderer::BeginFrame();

    //GAME STATES
    if (wager == -1) { //wager hasn't been made
//        Renderer::DrawTexturedQuad({0, 0}, {2.0f, 2.0f}, blackJackDeck.cardBack1);
//        Renderer::DrawQuad({0, 0}, {1.0, 1.5}, {1, 1, 1, 1});
//        Renderer::DrawTexturedQuad({0, 0}, {1.0f, 1.0f}, BJtextures[0]);
//
//        if (GUI::Button({-0.5f, -0.55f}, {0.4f, 0.4f}, BJtextures[1])) {
//            wager = 1;
//        }
//        if (GUI::Button({0.0f, -0.55f}, {0.4f, 0.4f}, BJtextures[2])) {
//            wager = 5;
//        }
//        if (GUI::Button({0.5f, -0.55f}, {0.4f, 0.4f}, BJtextures[3])) {
//            wager = 10;
//        }
// toggles the state of interface
        Renderer::DrawTexturedQuad({0, 0}, {2.0f, 2.0f}, blackJackDeck.cardBack1);
        Renderer::DrawQuad({0, 0}, {1.0, 1.5}, {1, 1, 1, 1});
        Renderer::DrawTexturedQuad({0, 0}, {1.0f, 1.0f}, BJtextures[0]);
        if (GUI::Button({ 0.0f, -0.55f }, { 0.4f, 0.4f }, BJtextures[3]) && !s_inputInterfaceOpen) {
            s_inputInterfaceOpen = !s_inputInterfaceOpen;
        }
// renders the interface
        else if (s_inputInterfaceOpen) {
            Renderer::DrawQuad({ 0.0f, 0.0f }, { 0.4f, 0.4f }, { 0.0f, 0.0f, 0.0f, 0.25f });
            int32_t amount = GUI::InputNumberInterface();
            // input number interface has given a valid amount to work with
            if (amount > 0) {
                // do something with the amount wagered
                // ...
                s_inputInterfaceOpen = false;
                wager = amount;
            }
                // user has insufficient funds
            else if (amount < 0) {
                s_inputInterfaceOpen = false;
                wager = -1;
            }
        }
    }

    else if (BJWin) {
        //DRAW HANDS
        for (int i = 0; i < 11; i++) {
            if (handTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), -0.6}, {0.3f, 0.4f}, handTextures[i]);
            if (aiHandTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), 0.6}, {0.3f, 0.4f}, aiHandTextures[i]);
        }
        Renderer::DrawTexturedQuad({-0.5f, 0}, {1.0f, 0.5f}, BJtextures[4]);
        if (GUI::Button({1.0f, 0.5f}, {0.5f, 0.5f}, BJtextures[9])) {
            AccountManager::AddToBalance(wager);
            this->Close();
            return;
        }
        Renderer::DrawQuad({1.0f, -0.5f}, {0.5f, 0.5f},{1,1,1,1});
        if (GUI::Button({1.0f, -0.5f}, {0.5f, 0.5f}, BJtextures[10])) {
            AccountManager::AddToBalance(wager);
            blackJack_initialized = false;
        }
    } else if (BJLose) {
        //DRAW HANDS
        for (int i = 0; i < 11; i++) {
            if (handTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), -0.6}, {0.3f, 0.4f}, handTextures[i]);
            if (aiHandTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), 0.6}, {0.3f, 0.4f}, aiHandTextures[i]);
        }
        Renderer::DrawTexturedQuad({-0.5f, 0}, {1.0f, 0.5f}, BJtextures[5]);
        if (GUI::Button({1.0f, 0.5f}, {0.5f, 0.5f}, BJtextures[9])) {
            AccountManager::AddToBalance(wager*-1);
            this->Close();
            return;
        }
        Renderer::DrawQuad({1.0f, -0.5f}, {0.5f, 0.5f},{1,1,1,1});
        if (GUI::Button({1.0f, -0.5f}, {0.5f, 0.5f}, BJtextures[10])) {
            AccountManager::AddToBalance(wager*-1);
            blackJack_initialized = false;
        }
    } else if (BJTie) {
        //DRAW HANDS
        for (int i = 0; i < 11; i++) {
            if (handTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), -0.6}, {0.3f, 0.4f}, handTextures[i]);
            if (aiHandTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), 0.6}, {0.3f, 0.4f}, aiHandTextures[i]);
        }
        Renderer::DrawTexturedQuad({1.0f, 0}, {1.4f, 2.0f}, BJtextures[8]);
        if (GUI::Button({1.0f, 0.5f}, {0.5f, 0.5f}, BJtextures[9])) {
            this->Close();
            return;
        }
        Renderer::DrawQuad({1.0f, -0.5f}, {0.5f, 0.5f},{1,1,1,1});
        if (GUI::Button({1.0f, -0.5f}, {0.5f, 0.5f}, BJtextures[10])) {
            blackJack_initialized = false;
        }
    } else { //MAIN GAME:
        //DRAW DECK IN CENTER OF TABLE
        Renderer::DrawTexturedQuad({0, 0}, {0.3f, 0.4f}, blackJackDeck.cardBack1);

        //DRAW HANDS
        for (int i = 0; i < 11; i++) {
            if (handTextures[i])
                Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), -0.6}, {0.3f, 0.4f}, handTextures[i]);
            if (aiHandTextures[i]) { // Player cannot see the AI's cards
                if(i==0)
                    Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), 0.6}, {0.3f, 0.4f}, aiHandTextures[0]);
                else
                    Renderer::DrawTexturedQuad({-1.3 + (i * 0.25), 0.6}, {0.3f, 0.4f}, blackJackDeck.cardBack1);
            }
        }
        //HIT BUTTON
        if (GUI::Button({-1.0f, -0.1f}, {0.45f, 0.25f}, BJtextures[6])) {
            if (!player_stand[0]) {
                for (int i = 0; i < 11; i++) {
                    if (!handTextures[i]) {
                        int random_integer = -1;
                        int lowest = 1, highest = 52;
                        do {
                            random_integer = lowest + rand() % ((highest - lowest) + 1);
                        } while (blackJackDeck.cardDrawn[random_integer]);
                        handTextures[i] = blackJackDeck.cardTextures[random_integer];
                        handValues[i] = blackJackDeck.cardValues[random_integer];
                        blackJackDeck.cardDrawn[random_integer] = true;
                        break;
                    }
                }
            }

            if (!player_stand[1] && !BJLose && !BJWin && !BJTie)
                runAI();
        }
        //STAND BUTTON
        if (GUI::Button({1.0f, -0.1f}, {0.45f, 0.25f}, BJtextures[7])) {
            player_stand[0] = true;
            do {
                if (!BJLose && !BJWin && !BJTie)
                    runAI();
            } while (!player_stand[1]);
        }
        //AI Stand Notif
        if(player_stand[1])
            Renderer::DrawTexturedQuad({0.6, 0.6}, {1.0f, 0.7f}, BJtextures[11]);

    }//end of game states

    Renderer::EndFrame();
}

void Blackjack::Terminate() {
    blackJack_initialized = false;
    delete this;
}