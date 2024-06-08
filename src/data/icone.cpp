/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "icone.hpp"
#include "../workCodes.hpp"


// Loading single icone
Icone::Icone() {
    loadIcone("Game.ico");
}

// Loading icone with need name
void Icone::loadIcone(const std::string name) {
    // Getting icone data
    SDL_RWops* tempRW = loadObject("img/" + name);

    // Checking created data
    #if CHECK_CORRECTION
    if (tempRW == nullptr) {
        SDL_Log("Can't load game icone, %s", SDL_GetError());
        throw "Error with loading game icone";
        exit(ERR_FIL_ICO);
    }
    #endif

    // Setting window icone
    SDL_Surface *iconeImage = IMG_LoadICO_RW(tempRW);

    // Closing data for image
    SDL_RWclose(tempRW);

    // Checking created image
    #if CHECK_CORRECTION
    if (iconeImage == nullptr) {
        SDL_Log("Can't load game icone, %s", SDL_GetError());
        throw "Error with loading game icone";
        exit(ERR_FIL_ICO);
    }
    #endif

    // Setting window icone
    SDL_SetWindowIcon(window, iconeImage);

    // Clearing data of creating
    SDL_FreeSurface(iconeImage);
}
