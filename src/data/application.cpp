/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "application.hpp"
#include "../define.hpp"
#include "../workCodes.hpp"

// Function of creating window and renderer for outputing image
App::App() {
    // Initialising main SDL libarary
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("main library");
        #endif
    }

    // Creating main game window
    window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    #if CHECK_CORRECTION
    if (window == NULL) {
        throw LibararyLoadException("window creation");
    }
    #endif

    // Creating renderer from window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #if CHECK_CORRECTION
    if (renderer == NULL) {
        throw LibararyLoadException("renderer creation");
    }
    #endif
}

// Function of deleting window and renders
App::~App() {
    // Destroying renderer
    SDL_DestroyRenderer(renderer);

    // Destrying window
    SDL_DestroyWindow(window);

    // Closing SDL library
    SDL_Quit();
}

// Setting color for draw
void App::setColor(SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// Blitting all buffered objects
void App::render() {
    SDL_RenderPresent(renderer);
}
