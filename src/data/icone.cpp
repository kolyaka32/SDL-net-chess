/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "icone.hpp"
#include "../workCodes.hpp"


// Loading single icone
Icone::Icone() {
    loadIcone("img/Game.ico");
}

// Loading icone with need name
void Icone::loadIcone(const char *name) {
    // Getting icone data
    SDL_RWops* tempRW = loadObject(name);

    // Checking created data
    #if CHECK_CORRECTION
    if (tempRW == nullptr) {
        // Showing error
        SDL_Log("Can't load game icone, %s", SDL_GetError());
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
        // Showing error
        SDL_Log("Can't load game icone, %s", SDL_GetError());
        exit(ERR_FIL_ICO);
    }
    #endif

    // Setting window icone
    SDL_SetWindowIcon(window, iconeImage);

    // Clearing data of creating
    SDL_FreeSurface(iconeImage);
}
