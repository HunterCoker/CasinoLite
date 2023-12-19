#include "Games.hpp"
#include "../Deck.h"

#include "../../GUI/GUI.hpp"

using namespace std;

Ref<Texture> pokerTextures[20];
Ref<Texture> handCards[6];
Ref<Texture> community[5];

int pokerInit = false;
int folded[3];//if each player has folded or not
int pot = 0;//value of pot
int holeCards[6];
int playerFunds[3];
int roundPayed[3];
int communityCards[5];
int handWorth[3];//holds the "value" of the best hand on the table for each player
int blind;
int gameState;
int handsDealt;
int checkVal;
int holdB;
int raiseAmnts[] = {1, 5, 10, 50};
int raiser;
int potMaster[10];
int playerPot[10];
int bot1Pot[10];
int bot2Pot[10];
int spot;
int comShown;
int gameWon;
int net;

static bool s_inputInterfaceOpen = false;

Deck pDeck;


void Poker::Init() {
    srand(time(nullptr));
    for(int & i : folded){
        i = 0;
        handWorth[i] = 0;
    }
    for (int i = 0; i < 2; i++) {
        handCards[i] = nullptr;
    }
    for (int i = 0; i < 10; i++) {
        potMaster[i] = 0;
        playerPot[i] = 0;
        bot1Pot[i] = 0;
        bot2Pot[i] = 0;
    }
    handsDealt = 0;
    pot = 0;
    blind = -1;
    pDeck.Init();
    gameState = -1;
    blind++;
    holdB = blind;
    raiser = 0;
    spot = 1;
    checkVal = 1;
    potMaster[0] = 1;
    comShown = 0;
    gameWon = 0;
    net = 0;



    //set all textures here
    pokerTextures[0] = Texture::Create("../Assets/Textures/poker/poker_logo.png");
    pokerTextures[1] = Texture::Create("../Assets/Textures/chips/1_chip.png");
    pokerTextures[2] = Texture::Create("../Assets/Textures/chips/5_chip.png");
    pokerTextures[3] = Texture::Create("../Assets/Textures/chips/10_chip.png");
    pokerTextures[4] = Texture::Create("../Assets/Textures/chips/50_chip.png");

    pokerTextures[5] = Texture::Create("../Assets/Textures/poker/fold.png");
    pokerTextures[6] = Texture::Create("../Assets/Textures/poker/raise.png");
    pokerTextures[7] = Texture::Create("../Assets/Textures/poker/call.png");
    pokerTextures[8] = Texture::Create("../Assets/Textures/poker/folded.png");
    pokerTextures[9] = Texture::Create("../Assets/Textures/poker/raised.png");
    pokerTextures[10] = Texture::Create("../Assets/Textures/poker/called.png");
    pokerTextures[11] = Texture::Create("../Assets/Textures/rouletteTable/return.png");
    pokerTextures[12] = Texture::Create("../Assets/Textures/rouletteTable/playAgain.png");
    pokerTextures[13] = Texture::Create("../Assets/Textures/poker/winner.png");


    int dealtValue;
    //populate hands
    for (int i = 0; i < 6; i++) {
        do {
            dealtValue = 1 + rand() % 52;
        } while (pDeck.cardDrawn[dealtValue]);
        holeCards[i] = dealtValue;
        handCards[i] = pDeck.cardTextures[dealtValue];
        pDeck.cardDrawn[dealtValue] = true;
    }

    //populate the community cards
    for (int i = 0; i < 5; i++) {
        do {
            dealtValue = 1 + rand() % 52;
        } while (pDeck.cardDrawn[dealtValue]);
        communityCards[i] = dealtValue;
        community[i] = pDeck.cardTextures[dealtValue];
        pDeck.cardDrawn[dealtValue] = true;
    }




}




void aiBid(int player, int raisable){
    int move;
    if (raisable == 1){
        move = rand() % 100;
    }else{
        move = rand() % 70;
    }


    if(move < 10 && ((checkVal - roundPayed[player]) > 0)){//fold
        folded[player] = 1;
    }else if(move < 10){
        move += 10;
    }

    if(move >= 20 && move < 70){//call
        playerFunds[player] -= checkVal - roundPayed[player];
        pot += checkVal - roundPayed[player];

        if(player == 1){
            for (int i = 0; i < spot; i++) {
                bot1Pot[i] = potMaster[i];
            }
        }else{
            for (int i = 0; i < spot; i++) {
                bot2Pot[i] = potMaster[i];
            }
        }
        roundPayed[player] =+ checkVal - roundPayed[player];


        folded[player] = 2;
    }else if(move > 70){//raise
        int amnt = raiseAmnts[rand() % 4];
        playerFunds[0] -= amnt;
        pot += amnt;
        roundPayed[0] += amnt;
        checkVal += amnt;
        potMaster[spot] = amnt;
        spot++;
        if(player == 1){
            for (int i = 0; i < spot; i++) {
                bot1Pot[i] = potMaster[i];
            }
        }else{
            for (int i = 0; i < spot; i++) {
                bot2Pot[i] = potMaster[i];
            }
        }
        folded[player] = 3;
    }
}


void winner(){
    if(gameWon == 1){
        Renderer::DrawTexturedQuad({0 , -0.9}, {0.4f, 0.2f}, pokerTextures[13]);
    }else if(gameWon == -1){
        Renderer::DrawTexturedQuad({-1.3 , -0.6}, {0.4f, 0.2f}, pokerTextures[13]);
    }else if(gameWon == -2){
        Renderer::DrawTexturedQuad({1.3 , -0.6}, {0.4f, 0.2f}, pokerTextures[13]);
    }

}



void Poker::Update(float ts) {
    if (!pokerInit) {
        Init();
        pokerInit = true;
    }

    if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
        this->Close();
        return;
    }

    Renderer::ClearColor({0.0f, 0.2f, 0.0f, 1.0f});

    Renderer::BeginFrame();
    /* your code goes here */

    // toggles the state of interface
    if (gameState == -1) {
        Renderer::DrawTexturedQuad({0, 0}, {2.0f, 2.0f}, pDeck.cardBack1);
        Renderer::DrawQuad({0, 0}, {1.0, 1.3}, {1, 1, 1, 1});
        Renderer::DrawTexturedQuad({0.0f, 0.2}, {1, 1}, pokerTextures[0]);


        if (GUI::Button({0.0f, -0.45f}, {0.4f, 0.4f}, pokerTextures[3]) && !s_inputInterfaceOpen) {//add picture
            s_inputInterfaceOpen = !s_inputInterfaceOpen;
        }
        // renders the interface
        if (s_inputInterfaceOpen) {
            Renderer::DrawQuad({0.0f, 0.0f}, {0.4f, 0.4f}, {0.0f, 0.0f, 0.0f, 0.25f});
            int32_t amount = GUI::InputNumberInterface();

            // input number interface has given a valid amount to work with
            if (amount > 0) {
                // do something with the amount wagered
                for (int &playerFund: playerFunds) {
                    playerFund = amount;
                }

                s_inputInterfaceOpen = false;
                handsDealt = 1;
                gameState = 1;
            }
                // user has insufficient funds
            else if (amount < 0) {
                s_inputInterfaceOpen = false;
                gameState = 0;
            }
        }

    } else if (gameState == 1) {//first round
//        deal Hand cards



        if(holdB % 3 == 0){
            if (GUI::Button({1.0f, -0.5f}, {0.3f, 0.1f}, pokerTextures[5])) {
                folded[0] = 1;

                gameState = 6;
                return;

            }
            if (GUI::Button({1.0f, -0.7f}, {0.3f, 0.1f}, pokerTextures[6])&&(playerFunds[0] >= 1)) {
                raiser = 1;

            }
            if (GUI::Button({1.0f, -0.9f}, {0.3f, 0.1f}, pokerTextures[7])) {
                playerFunds[0] -= checkVal - roundPayed[0];
                pot += checkVal - roundPayed[0];
                playerFunds[0] = 0;
                for (int i = 0; i < spot; i++) {
                    playerPot[i] = potMaster[i];
                    playerFunds[0] += potMaster[i];
                }
                folded[0] = 2;
                ++holdB;
            }

        }else {
            if(folded[holdB % 3] != 1){
                aiBid(holdB % 3, 1);
            }
            holdB++;
        }
        if(holdB % 5 == blind + 3){
            gameState = 2;
        }






//
    } else if (gameState == 2) {
        if(holdB % 3 == 0){
            if((checkVal - roundPayed[0]) > 0){
                if (GUI::Button({1.0f, -0.5f}, {0.3f, 0.1f}, pokerTextures[5]) ) {
                    folded[0] = 1;
                    gameState = 6;
                    return;
                }
            }
            if (GUI::Button({1.0f, -0.9f}, {0.3f, 0.1f}, pokerTextures[7])) {
                playerFunds[0] -= checkVal - roundPayed[0];
                pot += checkVal - roundPayed[0];
                for (int i = 0; i < spot; i++) {
                    playerPot[i] = potMaster[i];
                }
                roundPayed[0] =+ checkVal - roundPayed[0];
                folded[0] = 2;
                holdB++;
            }

        }else {
            if(folded[holdB % 3] != 1){
                aiBid(holdB % 3, 0);
            }
            holdB++;
        }
        if(holdB == blind + 5){
            gameState = 3;
        }else if (holdB == blind + 10){
            gameState = 4;
        }else if(holdB == blind + 15){
            gameState = 5;
        }else if(holdB == blind + 20){
            gameState = 6;
        }


    } else if (gameState == 3) {
        comShown = 3;
        gameState = 1;
    } else if (gameState == 4) {
        comShown = 4;
        gameState = 1;
    }else if (gameState == 5) {
        comShown = 5;
        gameState = 1;
    }else if (gameState == 6){
        if(folded[0] != 1) {
            if(((holeCards[1] - (holeCards[0] - (holeCards[0] % 4))) < 4) && ((holeCards[1] - (holeCards[0] - (holeCards[0] % 4))) > 0)){
                handWorth[0] = (holeCards[0] / 4) + 20;
            }
            for (int i = 0; i < 2; i++) {
                if ((holeCards[i]/4) > handWorth[0]) {
                    handWorth[0] = holeCards[i] / 4;
                }
                for (int j = 0; j < 5; j++) {
                    if (((communityCards[j] - (holeCards[i] - (holeCards[i] % 4))) < 4) && ((communityCards[j] - (holeCards[i] - (holeCards[i] % 4))) > 0)) {
                        if (((holeCards[i]/4) + 20) > handWorth[0])
                            handWorth[0] = (holeCards[i] / 4) + 20;
                    }
                }

            }
        }
        if(folded[1] != 1) {
            if(((holeCards[3] - (holeCards[2] - (holeCards[2] % 4))) < 4) && ((holeCards[3] - (holeCards[2] - (holeCards[2] % 4))) > 0)){
                handWorth[1] = (holeCards[2] / 4) + 20;
            }
            for (int i = 2; i < 4; i++) {
                if((holeCards[i]/4) > handWorth[1]){
                    handWorth[1] = holeCards[i] / 4;
                }
                for (int j = 0; j < 5; j++) {
                    if (((communityCards[j] - (holeCards[i] - (holeCards[i] % 4))) < 4) && ((communityCards[j] - (holeCards[i] - (holeCards[i] % 4))) > 0)) {
                        if(((holeCards[i]/4) + 20) > handWorth[1])
                            handWorth[1] = (holeCards[i] / 4) + 20;
                    }
                }
            }
        }
        if(folded[2] != 1) {
            if(((holeCards[5] - (holeCards[4] - (holeCards[4] % 4))) < 4) && ((holeCards[5] - (holeCards[4] - (holeCards[4] % 4))) > 0)){
                handWorth[2] = (holeCards[4] / 4) + 20;
            }
            for (int i = 4; i < 6; i++) {
                if((holeCards[i]/4) > handWorth[2]){
                    handWorth[2] = holeCards[i] / 4;
                }

                for (int j = 0; j < 5; j++) {
                    if (((communityCards[j] - (holeCards[i] - (holeCards[i] % 4))) < 4) && ((communityCards[j] - (holeCards[i] - (holeCards[i] % 4))) > 0)) {
                        if(((holeCards[i]/4) + 20) > handWorth[2])
                            handWorth[2] = (holeCards[i]/4) + 20;
                    }
                }
            }
        }


        if((handWorth[0] > handWorth[1]) && (handWorth[0] > handWorth[2])){
            gameWon = 1;
        }else if(handWorth[1] > handWorth[2]){
            gameWon = -1;
        }else{
            gameWon = -2;
        }
        if(gameWon == 1){
            for (int i = 0; i < 10; i++) {
                net += playerPot[i];
                net += bot1Pot[i];
                net += bot2Pot[i];
            }
        }else{
            int i = 0;
            while (playerPot[i] != 0) {
                net -= playerPot[i];
                i++;
            }
        }
        gameState = 10;


    } else if (gameState == 10) {

        comShown = 5;
        winner();



        if (GUI::Button({-0.5, 0.3f}, {0.5f, 0.3f}, pokerTextures[11])) {
            AccountManager::AddToBalance(net);
            this->Close();
            return;
        }
        if (GUI::Button({-0.5, -0.25f}, {0.5f, 0.3f}, pokerTextures[12])) {
            AccountManager::AddToBalance(net);
            pokerInit = false;
        }

    }



    if(handsDealt == 1){
        Renderer::DrawTexturedQuad({-0.15, -0.6}, {0.3f, 0.4f}, handCards[0]);
        Renderer::DrawTexturedQuad({0.15, -0.6}, {0.3f, 0.4f}, handCards[1]);

        if (folded[1] != 1 && gameWon == 0) {
            Renderer::DrawTexturedQuad({-1.3, 0}, {0.3f, 0.4f}, pDeck.cardBack1);
            Renderer::DrawTexturedQuad({-1.3 + 0.3, 0}, {0.3f, 0.4f}, pDeck.cardBack1);
        }else{
            Renderer::DrawTexturedQuad({-1.3, -0.4}, {0.3f, 0.1f}, pokerTextures[8]);
        }
        if (folded[2] != 1 && gameWon == 0) {
            Renderer::DrawTexturedQuad({1.3, 0}, {0.3f, 0.4f}, pDeck.cardBack1);
            Renderer::DrawTexturedQuad({1.3 - 0.3, 0}, {0.3f, 0.4f}, pDeck.cardBack1);
        }else{
            Renderer::DrawTexturedQuad({1.3, -0.4}, {0.3f, 0.1f}, pokerTextures[8]);
        }
        if(folded[1] == 2){//called
            Renderer::DrawTexturedQuad({-1.3, -0.4}, {0.3f, 0.1f}, pokerTextures[10]);
        }else if(folded[1] == 3){//raised
            Renderer::DrawTexturedQuad({-1.3, -0.4}, {0.3f, 0.1f}, pokerTextures[9]);
        }
        if(folded[2] == 2){//called
            Renderer::DrawTexturedQuad({1.3, -0.4}, {0.3f, 0.1f}, pokerTextures[10]);
        }else if(folded[2] == 3){//raised
            Renderer::DrawTexturedQuad({1.3, -0.4}, {0.3f, 0.1f}, pokerTextures[9]);
        }
        if(gameWon != 0){
            Renderer::DrawTexturedQuad({-1.3, 0}, {0.3f, 0.4f}, handCards[2]);
            Renderer::DrawTexturedQuad({-1.3 + 0.3, 0}, {0.3f, 0.4f}, handCards[3]);
            Renderer::DrawTexturedQuad({1.3, 0}, {0.3f, 0.4f}, handCards[4]);
            Renderer::DrawTexturedQuad({1.3 - 0.3, 0}, {0.3f, 0.4f}, handCards[5]);
        }
    }
    if(raiser == 1){
        if (GUI::Button({-1.0f, -0.6f}, {0.2f, 0.2f}, pokerTextures[1])) {
            playerFunds[0] -= 1;
            pot += 1;
            roundPayed[0] += 1;
            checkVal += 1;
            folded[0] = 3;
            potMaster[spot] = 1;
            spot++;
            for (int i = 0; i < spot; i++) {
                playerPot[i] = potMaster[i];
            }
            ++holdB;
            raiser = 0;
        }
        if (GUI::Button({-0.8f, -0.6f}, {0.2f, 0.2f}, pokerTextures[2])&&(playerFunds[0] >=5)) {
            playerFunds[0] -= 5;
            pot += 5;
            roundPayed[0] += 5;
            checkVal += 5;
            folded[0] = 3;
            potMaster[spot] = 5;
            spot++;
            for (int i = 0; i < spot; i++) {
                playerPot[i] = potMaster[i];
            }
            ++holdB;
            raiser = 0;

        }
        if (GUI::Button({-1.0f, -0.8f}, {0.2f, 0.2f}, pokerTextures[3])&&(playerFunds[0] >=10)) {
            playerFunds[0] -= 10;
            pot += 10;
            roundPayed[0] += 10;
            checkVal += 10;
            folded[0] = 3;
            potMaster[spot] = 10;
            spot++;
            for (int i = 0; i < spot; i++) {
                playerPot[i] = potMaster[i];
            }
            ++holdB;
            raiser = 0;

        }
        if (GUI::Button({-0.8f, -0.8f}, {0.2f, 0.2f}, pokerTextures[4])&&(playerFunds[0] >=50)) {
            playerFunds[0] -= 50;
            pot += 50;
            roundPayed[0] += 50;
            checkVal += 50;
            folded[0] = 3;

            potMaster[spot] = 50;
            spot++;
            for (int i = 0; i < spot; i++) {
                playerPot[i] = potMaster[i];
            }
            ++holdB;
            raiser = 0;

        }
    }
    if(pot >0){
        for (int i = 0; i < 10; i++) {
            if(playerPot[i] == 1){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0.1}, {0.2f, 0.2f}, pokerTextures[1]);
            }else if(playerPot[i] == 5){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0.1}, {0.2f, 0.2f}, pokerTextures[2]);
            }else if(playerPot[i] == 10){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0.1}, {0.2f, 0.2f}, pokerTextures[3]);
            }else if(playerPot[i] == 50){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0.1}, {0.2f, 0.2f}, pokerTextures[4]);
            }
            if(bot1Pot[i] == 1){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0}, {0.2f, 0.2f}, pokerTextures[1]);
            }else if(bot1Pot[i] == 5){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0}, {0.2f, 0.2f}, pokerTextures[2]);
            }else if(bot1Pot[i] == 10){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0}, {0.2f, 0.2f}, pokerTextures[3]);
            }else if(bot1Pot[i] == 50){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, 0}, {0.2f, 0.2f}, pokerTextures[4]);
            }
            if(bot2Pot[i] == 1){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, -0.1}, {0.2f, 0.2f}, pokerTextures[1]);
            }else if(bot2Pot[i] == 5){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, -0.1}, {0.2f, 0.2f}, pokerTextures[2]);
            }else if(bot2Pot[i] == 10){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, -0.1}, {0.2f, 0.2f}, pokerTextures[3]);
            }else if(bot2Pot[i] == 50){
                Renderer::DrawTexturedQuad({-0.1 + i* 0.1, -0.1}, {0.2f, 0.2f}, pokerTextures[4]);
            }
        }
    }
    if(comShown > 0){
        for (int i = 0; i < comShown; i++) {
            Renderer::DrawTexturedQuad({-0.6 + i* 0.3, 0.7}, {0.3f, 0.4f}, community[i]);
        }
    }
    if((folded[1] == 1)&& (folded[2] == 1)){
        gameState = 6;

    }


    /* ------------------- */
    Renderer::EndFrame();
}
void Poker::Terminate() {


    delete this;
}
