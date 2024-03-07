#include "include.hpp"
#include "icone.hpp"
#include "workCodes.hpp"


Icone::Icone(){
    if(!loadIcone("img/Game.ico")){
        printf("Can't load game icone");
        exit(ERR_FIL_ICO);
    }
}

Icone::~Icone(){
    
}

bool Icone::loadIcone(const char *name){
    // Getting icone data
    SDL_RWops* tempRW = loadObject(name);

    // Checking created data
    if(tempRW == nullptr){
        // Showing error
        return false;
    }

    // Setting window icone
    SDL_Surface* iconeImage = IMG_LoadICO_RW(tempRW);

    // Closing data for image
    SDL_RWclose(tempRW);

    // Checking created image
    if(iconeImage == nullptr){
        // Showing error
        return false;
    }
    
    // Setting window icone
    SDL_SetWindowIcon(window, iconeImage);

    // Clearing data of creating
    SDL_FreeSurface(iconeImage);

    // Showing correct loading
    return true;
}