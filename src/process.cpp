#include "stdio.h"
#include "include.hpp"
#include "SDL_net.h"
#include "process.hpp"
#include "workCodes.hpp"

// Function of initialasing all libraries
Process::Process(){
    // Initialising main SDL libarary
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        printf("Couldn't initialise SDL main library: %s\n", SDL_GetError());
        exit(ERR_SDL_SDL);
    }

    // Initializing image library
    #if IMG_count
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Couldn't initialize image library: %s\n", IMG_GetError());
        exit(ERR_SDL_IMG);
    }
    #endif

    // Initializing fonts library
    #if FNT_count
    if(TTF_Init()){
        printf("Couldn't initialize font library: %s\n", TTF_GetError());
        exit(ERR_SDL_FFT);
    }
    #endif

    // Initializing audio library
    #if MUS_count || SND_count
    if(!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)){
        printf("Couldn't initialize audio library: %d\n", Mix_GetError());
        exit(ERR_SDL_SND);
    }
    #endif

    // Initialising network libarary
    #if BASE_PORT
    if(SDLNet_Init()){
        printf("Couldn't initialize network library: %s\n", SDLNet_GetError());
        exit(ERR_SDL_NET);
    }
    #endif
}


// Function of closing all outside libraries and files
Process::~Process(){
    // Closing all outside libraries in reverce order
    #if BASE_PORT
    SDLNet_Quit();    // Closing network libarary
    #endif
    #if MUS_count || SND_count
    Mix_CloseAudio();  // Closing audio player
    Mix_Quit();        // Closing mixer player
    #endif
    #if FNT_count
	TTF_Quit();        // Closing font library
    #endif
    #if IMG_count
    IMG_Quit();        // Closing image library
    #endif
    SDL_Quit();        // Closing main sdl library
}

// Main function of running process
int Process::run(){

    return 0;
}