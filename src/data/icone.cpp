/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "icone.hpp"
#include "loadExceptions.hpp"


// Loading single icone
Icone::Icone() {
    loadIcone("Game.ico");
}

// Loading icone with need name
void Icone::loadIcone(const std::string _name) {
    // Getting icone data
    SDL_RWops* tempRW = loadObject("img/" + _name);

    // Checking created data
    #if CHECK_CORRECTION
    if (tempRW == nullptr) {
        throw DataLoadException("icone file load: " + _name);
    }
    #endif

    // Setting window icone
    SDL_Surface *iconeImage = IMG_LoadICO_RW(tempRW);

    // Closing data for image
    SDL_RWclose(tempRW);

    // Checking created image
    #if CHECK_CORRECTION
    if (iconeImage == nullptr) {
        throw DataLoadException("icone file creation: " + _name);
    }
    #endif

    // Setting window icone
    SDL_SetWindowIcon(window, iconeImage);

    // Clearing data of creating
    SDL_FreeSurface(iconeImage);
}
