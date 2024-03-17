#include "icone.hpp"
#include "../workCodes.hpp"


// Loading single icone
Icone::Icone(){
    if(loadIcone("img/Game.ico")){
        #if CHECK_CORRECTION
        printf("Can't load game icone");
        exit(ERR_FIL_ICO);
        #endif
    }
}

// Loading icone with need name
bool Icone::loadIcone(const char *name){
    // Getting icone data
    SDL_RWops* tempRW = loadObject(name);

    // Checking created data
    #if CHECK_CORRECTION
    if(tempRW == nullptr){
        // Showing error
        return true;
    }
    #endif

    // Setting window icone
    SDL_Surface *iconeImage = IMG_LoadICO_RW(tempRW);

    // Closing data for image
    SDL_RWclose(tempRW);

    // Checking created image
    #if CHECK_CORRECTION
    if(iconeImage == nullptr){
        // Showing error
        return true;
    }
    #endif
    
    // Setting window icone
    SDL_SetWindowIcon(window, iconeImage);

    // Clearing data of creating
    SDL_FreeSurface(iconeImage);

    // Showing correct loading
    return false;
}