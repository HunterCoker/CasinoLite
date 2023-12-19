//
// Created by Connor on 2023-11-12.
//
//#include "../../GUI/GUI.hpp"
#include "Deck.h"

void Deck::Init() {
    this->cardValues[0] = 2;
    this->cardValues[1] = 2;
    this->cardValues[2] = 2;
    this->cardValues[3] = 2;
    this->cardValues[4] = 3;
    this->cardValues[5] = 3;
    this->cardValues[6] = 3;
    this->cardValues[7] = 3;
    this->cardValues[8] = 4;
    this->cardValues[9] = 4;
    this->cardValues[10] = 4;
    this->cardValues[11] = 4;
    this->cardValues[12] = 5;
    this->cardValues[13] = 5;
    this->cardValues[14] = 5;
    this->cardValues[15] = 5;
    this->cardValues[16] = 6;
    this->cardValues[17] = 6;
    this->cardValues[18] = 6;
    this->cardValues[19] = 6;
    this->cardValues[20] = 7;
    this->cardValues[21] = 7;
    this->cardValues[22] = 7;
    this->cardValues[23] = 7;
    this->cardValues[24] = 8;
    this->cardValues[25] = 8;
    this->cardValues[26] = 8;
    this->cardValues[27] = 8;
    this->cardValues[28] = 9;
    this->cardValues[29] = 9;
    this->cardValues[30] = 9;
    this->cardValues[31] = 9;
    this->cardValues[32] = 10;
    this->cardValues[33] = 10;
    this->cardValues[34] = 10;
    this->cardValues[35] = 10;
    this->cardValues[36] = 1;
    this->cardValues[37] = 1;
    this->cardValues[38] = 1;
    this->cardValues[39] = 1;
    this->cardValues[40] = 11;
    this->cardValues[41] = 11;
    this->cardValues[42] = 11;
    this->cardValues[43] = 11;
    this->cardValues[44] = 13;
    this->cardValues[45] = 13;
    this->cardValues[46] = 13;
    this->cardValues[47] = 13;
    this->cardValues[48] = 12;
    this->cardValues[49] = 12;
    this->cardValues[50] = 12;
    this->cardValues[51] = 12;


    this->cardBack1 = Texture::Create("../Assets/Textures/deck-of-cards/Back2.png");
    for(bool & i : this->cardDrawn){
        i = false;
    }

    this->cardTextures[0] = Texture::Create("../Assets/Textures/deck-of-cards/2.2.png");
    this->cardTextures[1] = Texture::Create("../Assets/Textures/deck-of-cards/2.4.png");
    this->cardTextures[2] = Texture::Create("../Assets/Textures/deck-of-cards/2.5.png");
    this->cardTextures[3] = Texture::Create("../Assets/Textures/deck-of-cards/2.7.png");
    this->cardTextures[4] = Texture::Create("../Assets/Textures/deck-of-cards/3.2.png");
    this->cardTextures[5] = Texture::Create("../Assets/Textures/deck-of-cards/3.4.png");
    this->cardTextures[6] = Texture::Create("../Assets/Textures/deck-of-cards/3.5.png");
    this->cardTextures[7] = Texture::Create("../Assets/Textures/deck-of-cards/3.7.png");
    this->cardTextures[8] = Texture::Create("../Assets/Textures/deck-of-cards/4.2.png");
    this->cardTextures[9] = Texture::Create("../Assets/Textures/deck-of-cards/4.4.png");
    this->cardTextures[10] = Texture::Create("../Assets/Textures/deck-of-cards/4.5.png");
    this->cardTextures[11] = Texture::Create("../Assets/Textures/deck-of-cards/4.7.png");
    this->cardTextures[12] = Texture::Create("../Assets/Textures/deck-of-cards/5.2.png");
    this->cardTextures[13] = Texture::Create("../Assets/Textures/deck-of-cards/5.4.png");
    this->cardTextures[14] = Texture::Create("../Assets/Textures/deck-of-cards/5.5.png");
    this->cardTextures[15] = Texture::Create("../Assets/Textures/deck-of-cards/5.7.png");
    this->cardTextures[16] = Texture::Create("../Assets/Textures/deck-of-cards/6.2.png");
    this->cardTextures[17] = Texture::Create("../Assets/Textures/deck-of-cards/6.4.png");
    this->cardTextures[18] = Texture::Create("../Assets/Textures/deck-of-cards/6.5.png");
    this->cardTextures[19] = Texture::Create("../Assets/Textures/deck-of-cards/6.7.png");
    this->cardTextures[20] = Texture::Create("../Assets/Textures/deck-of-cards/7.2.png");
    this->cardTextures[21] = Texture::Create("../Assets/Textures/deck-of-cards/7.4.png");
    this->cardTextures[22] = Texture::Create("../Assets/Textures/deck-of-cards/7.5.png");
    this->cardTextures[23] = Texture::Create("../Assets/Textures/deck-of-cards/7.7.png");
    this->cardTextures[24] = Texture::Create("../Assets/Textures/deck-of-cards/8.2.png");
    this->cardTextures[25] = Texture::Create("../Assets/Textures/deck-of-cards/8.4.png");
    this->cardTextures[26] = Texture::Create("../Assets/Textures/deck-of-cards/8.5.png");
    this->cardTextures[27] = Texture::Create("../Assets/Textures/deck-of-cards/8.7.png");
    this->cardTextures[28] = Texture::Create("../Assets/Textures/deck-of-cards/9.2.png");
    this->cardTextures[29] = Texture::Create("../Assets/Textures/deck-of-cards/9.4.png");
    this->cardTextures[30] = Texture::Create("../Assets/Textures/deck-of-cards/9.5.png");
    this->cardTextures[31] = Texture::Create("../Assets/Textures/deck-of-cards/9.7.png");
    this->cardTextures[32] = Texture::Create("../Assets/Textures/deck-of-cards/10.2.png");
    this->cardTextures[33] = Texture::Create("../Assets/Textures/deck-of-cards/10.4.png");
    this->cardTextures[34] = Texture::Create("../Assets/Textures/deck-of-cards/10.5.png");
    this->cardTextures[35] = Texture::Create("../Assets/Textures/deck-of-cards/10.7.png");
    this->cardTextures[36] = Texture::Create("../Assets/Textures/deck-of-cards/A.2.png");
    this->cardTextures[37] = Texture::Create("../Assets/Textures/deck-of-cards/A.4.png");
    this->cardTextures[38] = Texture::Create("../Assets/Textures/deck-of-cards/A.5.png");
    this->cardTextures[39] = Texture::Create("../Assets/Textures/deck-of-cards/A.7.png");
    this->cardTextures[40] = Texture::Create("../Assets/Textures/deck-of-cards/J2.png");
    this->cardTextures[41] = Texture::Create("../Assets/Textures/deck-of-cards/J4.png");
    this->cardTextures[42] = Texture::Create("../Assets/Textures/deck-of-cards/J5.png");
    this->cardTextures[43] = Texture::Create("../Assets/Textures/deck-of-cards/J7.png");
    this->cardTextures[44] = Texture::Create("../Assets/Textures/deck-of-cards/K2.png");
    this->cardTextures[45] = Texture::Create("../Assets/Textures/deck-of-cards/K4.png");
    this->cardTextures[46] = Texture::Create("../Assets/Textures/deck-of-cards/K5.png");
    this->cardTextures[47] = Texture::Create("../Assets/Textures/deck-of-cards/K7.png");
    this->cardTextures[48] = Texture::Create("../Assets/Textures/deck-of-cards/Q2.png");
    this->cardTextures[49] = Texture::Create("../Assets/Textures/deck-of-cards/Q4.png");
    this->cardTextures[50] = Texture::Create("../Assets/Textures/deck-of-cards/Q5.png");
    this->cardTextures[51] = Texture::Create("../Assets/Textures/deck-of-cards/Q7.png");
}