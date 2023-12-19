#include "Games.hpp"

#include "../../GUI/GUI.hpp"

#include <chrono>
#include <algorithm>

using namespace std::chrono;
using namespace std;

Ref<Texture> chips[6];
Ref<Texture> numbers[38];
Ref<Texture> table[22];

int rouletteInitialized = false;
int bettingAmount = 0;
double betAmount = 0.0;
int number[19] = {0};
int betSize = 0;
int landed = 0;
bool spin = false;
bool stop = false;
bool playAgain = false;

static bool s_inputInterfaceOpen = false;

void Roulette::Init() {
    srand(static_cast<unsigned int>(time(0)));

    chips[0] = Texture::Create("../Assets/Textures/chips/1_chip.png");
    chips[1] = Texture::Create("../Assets/Textures/chips/5_chip.png");
    chips[2] = Texture::Create("../Assets/Textures/chips/10_chip.png");
    chips[3] = Texture::Create("../Assets/Textures/chips/50_chip.png");
    chips[4] = Texture::Create("../Assets/Textures/chips/100_chip.png");
    chips[5] = Texture::Create("../Assets/Textures/chips/500_chip.png");

    table[0] = Texture::Create("../Assets/Textures/rouletteTable/doublezero.png");
    table[1] = Texture::Create("../Assets/Textures/rouletteTable/zero.png");
    table[2] = Texture::Create("../Assets/Textures/rouletteTable/2to1.png");
    table[3] = Texture::Create("../Assets/Textures/rouletteTable/1st12.png");
    table[4] = Texture::Create("../Assets/Textures/rouletteTable/2nd12.png");
    table[5] = Texture::Create("../Assets/Textures/rouletteTable/3rd12.png");
    table[6] = Texture::Create("../Assets/Textures/rouletteTable/1to18.png");
    table[7] = Texture::Create("../Assets/Textures/rouletteTable/19to36.png");
    table[8] = Texture::Create("../Assets/Textures/rouletteTable/even.png");
    table[9] = Texture::Create("../Assets/Textures/rouletteTable/odd.png");
    table[10] = Texture::Create("../Assets/Textures/rouletteTable/red.png");
    table[11] = Texture::Create("../Assets/Textures/rouletteTable/black.png");
    table[12] = Texture::Create("../Assets/Textures/rouletteTable/wheel.png");
    table[13] = Texture::Create("../Assets/Textures/rouletteTable/ball.png");
    table[14] = Texture::Create("../Assets/Textures/rouletteTable/spin.png");
    table[15] = Texture::Create("../Assets/Textures/rouletteTable/stop.png");
    table[16] = Texture::Create("../Assets/Textures/rouletteTable/playAgain.png");
    table[17] = Texture::Create("../Assets/Textures/rouletteTable/winner.png");
    table[18] = Texture::Create("../Assets/Textures/rouletteTable/plus.png");
    table[19] = Texture::Create("../Assets/Textures/rouletteTable/lose.png");
    table[20] = Texture::Create("../Assets/Textures/rouletteTable/minus.png");
    table[21] = Texture::Create("../Assets/Textures/rouletteTable/return.png");

    for(int i = 0; i < 36; i++) {
        numbers[i] = Texture::Create("../Assets/Textures/rouletteTable/" + to_string(i + 1) + ".png");
    }
    numbers[36] = Texture::Create("../Assets/Textures/rouletteTable/00.png");
    numbers[37] = Texture::Create("../Assets/Textures/rouletteTable/0.png");

}

void Roulette::Update(float ts) {
    if(!rouletteInitialized){
        Init();
        rouletteInitialized = true;
    }

    if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
        this->Close();
        return;
    }

//    int width = Renderer::GetWindowWidth();
//    int height = Renderer::GetWindowHeight();
    static float acc_ts = 0.0f;
    acc_ts += ts;

    // Clear the screen with any color to make sure you're rendering on a clean canvas
    Renderer::ClearColor({ 0.0f, 0.2f, 0.0f, 1.0f });

    Renderer::BeginFrame();

    if(!bettingAmount) {
        playAgain = false;
        Renderer::ClearColor({ 0.0f, 0.2f, 0.0f, 1.0f });

        if (GUI::CircleButton({ -1.0f, 0.5f }, 0.4f, chips[0])) {
            if(1.0 <= AccountManager::GetBalance()){
                bettingAmount = 1;
                betAmount = 1.0;
            }
            else{
                betAmount = -1.0;
            }
            cout << "submitted amount: " << betAmount << endl;
            return;
        }
        if (GUI::CircleButton({ 0.0f, 0.5f }, 0.4f, chips[1])) {
            if(5.0 <= AccountManager::GetBalance()){
                bettingAmount = 2;
                betAmount = 5.0;
            }
            else{
                betAmount = -5.0;
            }
            cout << "submitted amount: " << betAmount << endl;
            return;
        }
        if (GUI::CircleButton({ 1.0f, 0.5f }, 0.4f, chips[2])) {
            if(10.0 <= AccountManager::GetBalance()){
                bettingAmount = 3;
                betAmount = 10.0;
            }
            else{
                betAmount = -10.0;
            }
            cout << "submitted amount: " << betAmount << endl;
            return;
        }
        if (GUI::CircleButton({ -1.0f, -0.5f }, 0.4f, chips[3])) {
            if(50.0 <= AccountManager::GetBalance()){
                bettingAmount = 4;
                betAmount = 50.0;
            }
            else{
                betAmount = -50.0;
            }
            cout << "submitted amount: " << betAmount << endl;
            return;
        }
        if (GUI::CircleButton({ 0.0f, -0.5f }, 0.4f, chips[4])) {
            if(100.0 <= AccountManager::GetBalance()){
                bettingAmount = 5;
                betAmount = 100.0;
            }
            else{
                betAmount = -100.0;
            }
            cout << "submitted amount: " << betAmount << endl;
            return;
        }
        if (GUI::CircleButton({ 1.0f, -0.5f }, 0.4f, chips[5])) {
            if(500.0 <= AccountManager::GetBalance()){
                bettingAmount = 6;
                betAmount = 500.0;
            }
            else{
                betAmount = -500.0;
            }
            cout << "submitted amount: " << betAmount << endl;
            return;
        }
    }
    else if(!betSize){
        Renderer::ClearColor({ 0.0f, 0.2f, 0.0f, 1.0f });

        float radius = 0.08;
        float width = 0.02 + radius;

        if(GUI::CircleButton({-11.0 * width, 0.2f}, radius, numbers[0])){
            number[0] = 1;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-11.0 * width, 0.45f}, radius, numbers[1])){
            number[0] = 2;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-11.0 * width, 0.7f}, radius, numbers[2])){
            number[0] = 3;
            betSize = 1;
            return;
        }
        if (GUI::CircleButton({ -9.0 * width, 0.2f }, radius, numbers[3])) {
            number[0] = 4;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-9.0 * width, 0.45f}, radius, numbers[4])){
            number[0] = 5;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-9.0 * width, 0.7f}, radius, numbers[5])){
            number[0] = 6;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-7.0 * width, 0.2f}, radius, numbers[6])){
            number[0] = 7;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-7.0 * width, 0.45f}, radius, numbers[7])){
            number[0] = 8;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-7.0 * width, 0.7f}, radius, numbers[8])){
            number[0] = 9;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-5.0 * width, 0.2f}, radius, numbers[9])){
            number[0] = 10;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-5.0 * width, 0.45f}, radius, numbers[10])){
            number[0] = 11;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-5.0 * width, 0.7f}, radius, numbers[11])){
            number[0] = 12;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-3.0 * width, 0.2f}, radius, numbers[12])){
            number[0] = 13;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-3.0 * width, 0.45f}, radius, numbers[13])){
            number[0] = 14;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-3.0 * width, 0.7f}, radius, numbers[14])){
            number[0] = 15;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-1.0 * width, 0.2f}, radius, numbers[15])){
            number[0] = 16;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-1.0 * width, 0.45f}, radius, numbers[16])){
            number[0] = 17;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({-1.0 * width, 0.7f}, radius, numbers[17])){
            number[0] = 18;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({1.0 * width, 0.2f}, radius, numbers[18])){
            number[0] = 19;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({1.0 * width, 0.45f}, radius, numbers[19])){
            number[0] = 20;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({1.0 * width, 0.7f}, radius, numbers[20])){
            number[0] = 21;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({3.0 * width, 0.2f}, radius, numbers[21])){
            number[0] = 22;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({3.0 * width, 0.45f}, radius, numbers[22])){
            number[0] = 23;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({3.0 * width, 0.7f}, radius, numbers[23])){
            number[0] = 24;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({5.0 * width, 0.2f}, radius, numbers[24])){
            number[0] = 25;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({5.0 * width, 0.45f}, radius, numbers[25])){
            number[0] = 26;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({5.0 * width, 0.7f}, radius, numbers[26])){
            number[0] = 27;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({7.0 * width, 0.2f}, radius, numbers[27])){
            number[0] = 28;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({7.0 * width, 0.45f}, radius, numbers[28])){
            number[0] = 29;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({7.0 * width, 0.7f}, radius, numbers[29])){
            number[0] = 30;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({9.0 * width, 0.2f}, radius, numbers[30])){
            number[0] = 31;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({9.0 * width, 0.45f}, radius, numbers[31])){
            number[0] = 32;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({9.0 * width, 0.7f}, radius, numbers[32])){
            number[0] = 33;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({11.0 * width, 0.2f}, radius, numbers[33])){
            number[0] = 34;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({11.0 * width, 0.45f}, radius, numbers[34])){
            number[0] = 35;
            betSize = 1;
            return;
        }
        if(GUI::CircleButton({11.0 * width, 0.7f}, radius, numbers[35])){
            number[0] = 36;
            betSize = 1;
            return;
        }
        //00
        if(GUI::Button({ -1.4f, 0.63f }, { 0.37f, 0.35f }, table[0])){
            number[0] = 37;
            betSize = 1;
            return;
        }
        //0
        if(GUI::Button({ -1.4f, 0.27f }, { 0.35f, 0.35f }, table[1])){
            number[0] = 38;
            betSize = 1;
            return;
        }
        //2 to 1 top row
        if(GUI::Button({13.0 * width, 0.7f}, {0.22f, 0.22f}, table[2])){
            for(int i = 0; i < 12; i++) {
                number[i] = 3 * (i + 1);
            }
            betSize = 12;
            return;
        }
        //2 to 1 middle row
        if(GUI::Button({13.0 * width, 0.45f}, {0.22f, 0.22f}, table[2])){
            for(int i = 0; i < 12; i++) {
                number[i] = 3 * (i + 1) - 1;
            }
            betSize = 12;
            return;
        }
        //2 to 1 bottom row
        if(GUI::Button({13.0 * width, 0.2f}, {0.22f, 0.22f}, table[2])){
            for(int i = 0; i < 12; i++) {
                number[i] = 3 * (i + 1) - 2;
            }
            betSize = 12;
            return;
        }
        //1st 12
        if(GUI::Button({-8.0 * width, -0.2f}, {7.5 * width, 0.38f}, table[3])){
            for(int i = 0; i < 12; i++){
                number[i] = i + 1;
            }
            betSize = 12;
            return;
        }
        //2nd 12
        if(GUI::Button({0.0, -0.2f}, {7.5 * width, 0.38f}, table[4])){
            for(int i = 0; i < 12; i++){
                number[i] = i + 13;
            }
            betSize = 12;
            return;
        }
        //3rd 12
        if(GUI::Button({8.0 * width, -0.2f}, {7.5 * width, 0.38f}, table[5])){
            for(int i = 0; i < 12; i++){
                number[i] = i + 25;
            }
            betSize = 12;
            return;
        }
        //1 to 18
        if(GUI::Button({-10.0 * width, -0.55f}, {3.75 * width, 0.28f}, table[6])){
            for(int i = 0; i < 18; i++){
                number[i] = i + 1;
            }
            betSize = 18;
            return;
        }
        //19 to 36
        if(GUI::Button({10.0 * width, -0.55f}, {3.75 * width, 0.28f}, table[7])){
            for(int i = 0; i < 18; i++){
                number[i] = i + 19;
            }
            betSize = 18;
            return;
        }
        //Even
        if(GUI::Button({-6.0 * width, -0.55f}, {3.75 * width, 0.28f}, table[8])){
            for(int i = 0; i < 18; i++){
                number[i] = (i + 1) * 2;
            }
            betSize = 18;
            return;
        }
        //Odd
        if(GUI::Button({6.0 * width, -0.55f}, {3.75 * width, 0.28f}, table[9])){
            for(int i = 0; i < 18; i++){
                number[i] = (i + 1) * 2 - 1;
            }
            betSize = 18;
            return;
        }
        //Red
        if(GUI::Button({-2.0 * width, -0.55f}, {3.75 * width, 0.28f}, table[10])){
            int reds[19] = {1, 3, 5, 7, 9, 12, 14,
                            16, 18, 19, 21, 23, 25,
                            27, 30, 32, 34, 35, 36};
            for(int i = 0; i < 19; i++){
                number[i] = reds[i];
            }
            betSize = 19;
            return;
        }
        //Black
        if(GUI::Button({2.0 * width, -0.55f}, {3.75 * width, 0.28f}, table[11])){
            int blacks[17] = {2, 4, 6, 8, 10, 11, 13,
                              15, 17, 20, 22, 24, 26,
                              28, 29, 31, 33};
            for(int i = 0; i < 17; i++){
                number[i] = blacks[i];
            }
            betSize = 17;
            return;
        }

    }
    else if(!spin){
        Renderer::ClearColor({0.0f, 0.2f, 0.0f, 1.0f});

        Renderer::DrawTexturedQuad({-0.7f, 0.0f}, {1.7f, 1.7f}, table[13]);
        Renderer::DrawTexturedQuad({-0.7f, 0.0f}, {1.3f, 1.3f}, table[12]);

        if (GUI::Button({1.0f, 0.0f}, {0.8f, 0.4f}, table[14])) {
            spin = true;
        }
    }
    else if(!stop){
        Renderer::ClearColor({0.0f, 0.2f, 0.0f, 1.0f});

        Renderer::DrawRotatedTexturedQuad({-0.7f, 0.0f}, {1.7f, 1.7f}, acc_ts * -30.0f, table[13], 1.0f);
        Renderer::DrawRotatedTexturedQuad({-0.7f, 0.0f}, {1.3f, 1.3f}, acc_ts * 40.0f, table[12], 1.0f);

        if (GUI::Button({1.0f, 0.0f}, {0.8f, 0.4f}, table[15])) {
            stop = true;
            return;
        }
    }
    else if(!playAgain){
        bool winner = false;

        Renderer::ClearColor({0.0f, 0.2f, 0.0f, 1.0f});
        if (!landed) {
            landed = rand() % 38 + 1;
        }
        Renderer::DrawTexturedQuad({-0.5f, 0.5f}, {0.5f, 0.5f}, numbers[landed - 1]);

        for(int i = 0; i < betSize; i++){
            if(number[i] == landed){
                winner = true;
            }
        }
        if(winner){
            Renderer::DrawTexturedQuad({-0.5f, 0.0f}, {1.0f, 0.4f}, table[17]);
            Renderer::DrawTexturedQuad({-1.1f, -0.5f}, {0.5f, 0.5f}, table[18]);
            Renderer::DrawTexturedQuad({-0.6f, -0.5f}, {0.5f, 0.5f}, chips[bettingAmount - 1]);
            Renderer::DrawTexturedQuad({-0.3f, -0.5f}, {0.5f, 0.5f}, chips[bettingAmount - 1]);
            AccountManager::AddToBalance(betAmount * 2);
            betAmount = 0.0;
        }
        else{
            Renderer::DrawTexturedQuad({-0.5f, 0.0f}, {1.0f, 0.4f}, table[19]);
            Renderer::DrawTexturedQuad({-0.8f, -0.5f}, {0.5f, 0.5f}, table[20]);
            Renderer::DrawTexturedQuad({-0.3f, -0.5f}, {0.5f, 0.5f}, chips[bettingAmount - 1]);
            AccountManager::AddToBalance(betAmount * -1);
            betAmount = 0.0;
        }

        if(GUI::Button({0.7f, 0.3f}, {1.0f, 0.5f}, table[16])){
            bettingAmount = 0;
            for(int i = 0; i < 19; i++){
                number[i] = 0;
            }
            betSize = 0;
            landed = 0;
            spin = false;
            stop = false;
            playAgain = true;
            return;
        }
        if(GUI::Button({0.7f, -0.3f}, {1.0f, 0.5f}, table[21])){
            bettingAmount = 0;
            for(int i = 0; i < 19; i++){
                number[i] = 0;
            }
            betSize = 0;
            landed = 0;
            spin = false;
            stop = false;

            this->Close();
            return;
        }
    }

    Renderer::EndFrame();
}

void Roulette::Terminate() {


    delete this;
}