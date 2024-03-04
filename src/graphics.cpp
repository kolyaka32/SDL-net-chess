#include "include.hpp"
#include "graphics.hpp"
#include "workCodes.hpp"


GraphicsLibrary::GraphicsLibrary(){
    // Initializing image library
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Couldn't initialize image library: %s\n", IMG_GetError());
        exit(ERR_SDL_IMG);
    }
}

GraphicsLibrary::~GraphicsLibrary(){
    // Closing image library
    IMG_Quit();
}


Textures::Textures(){
    
}

Textures::~Textures(){
    // Clearing all textures after work
    for(Uint8 i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(textures[i]);
    }
}
