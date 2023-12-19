//
// Created by Connor on 2023-11-12.
//
#include "../../GUI/GUI.hpp"
#ifndef CASINOLITE_DECK_H
#define CASINOLITE_DECK_H

class Deck{
public:
    Ref<Texture> cardBack1;
    Ref<Texture> cardTextures[52];
    int cardValues[52];
    bool cardDrawn[52];
    void Init();
};


#endif //CASINOLITE_DECK_H
