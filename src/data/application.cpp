#include "application.hpp"
#include "../define.hpp"
#include "../workCodes.hpp"

// Function of creating window and renderer for outputing image
App::App(){
    // Initialising main SDL libarary
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        #if CHECK_CORRECTION
        printf("Couldn't initialise SDL main library: %s\n", SDL_GetError());
        exit(ERR_SDL_SDL);
        #endif
    }

    // Creating main game window
    window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    #if CHECK_CORRECTION
    if(window == NULL){
        printf("Couldn't create window.\n");
        exit(ERR_INI_WIN);
    }
    #endif

    // Creating renderer from window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #if CHECK_CORRECTION
    if(renderer == NULL){
        printf("Couldn't create renderer.\n");
        exit(ERR_INI_REN);
    }
    #endif
    
    // Setting base drawing color
    setColor(BLACK);
};

// Function of deleting window and renders
App::~App(){
    // Destroying renderer
	SDL_DestroyRenderer(renderer);
    
    // Destrying window
	SDL_DestroyWindow(window);

    // Closing SDL library
    SDL_Quit();
};

// Setting color for draw
void App::setColor(SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
};

//
void App::render(){
    // Blocking any drawing
    drawMutex.lock();

    // Blitting all buffered objects
    SDL_RenderPresent(renderer);

    // Unlocking for other actions
    drawMutex.unlock();
};
