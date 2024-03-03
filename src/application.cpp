#include "include.hpp"
#include "define.hpp"
#include "iostream"
#include "values.hpp"
#include "application.hpp"
#include "workCodes.hpp"

// Function of creating window and renderer for outputing image
App::App(){
    // Creating main game window
    window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(window == NULL){
        printf("Couldn't create window.\n");
        exit(ERR_INI_WIN);
    }

    // Creating renderer from window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("Couldn't create renderer.\n");
        exit(ERR_INI_REN);
    }
    // Setting base drawing color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Openning audio chanel
    #if MUS_count || SND_count
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){
        printf("Couldn't initialase audio chanel.\n");
        exit(ERR_INI_SND);
    }
    #endif
}

// Function of deleting window and renders
App::~App(){
    #if MUS_count || SND_count
    Mix_CloseAudio();               // Closing audio library
    #endif
	SDL_DestroyRenderer(renderer);  // Destroying renderer
	SDL_DestroyWindow(window);      // Destrying window
}