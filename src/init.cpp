#include "stdio.h"
#include "include.hpp"
#include "SDL_net.h"
#include "values.hpp"

#include "init.hpp"

// Function of initialasing all libraries
void initLibraries(){
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

// Function of creating window and renderer for outputing image
void createVideo(){
    // Creating main game window
    app.window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(app.window == NULL){
        printf("Couldn't create window.\n");
        exit(ERR_INI_WIN);
    }

    // Creating renderer from window
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if(app.renderer == NULL){
        printf("Couldn't create renderer.\n");
        exit(ERR_INI_REN);
    }
    // Setting base drawing color
    SDL_SetRenderDrawColor(app.renderer, BACKGROUND_COLOR);

    // Openning audio chanel
    #if MUS_count || SND_count
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){
        printf("Couldn't initialase audio chanel.\n");
        exit(ERR_INI_SND);
    }
    #endif
}

// Function of deleting window and renders
void deleteVideo(){
    #if MUS_count || SND_count
    Mix_CloseAudio();                   // Closing audio library
    #endif
	SDL_DestroyRenderer(app.renderer);  // Destroying renderer
	SDL_DestroyWindow(app.window);      // Destrying window
}

// Function of closing all outside libraries and files
void exitLibraries(){
    // Closing all outside libraries
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
