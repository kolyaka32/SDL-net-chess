/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "libraries.hpp"
#include "logger.hpp"
// External libraries for initialisation
#include <SDL3/SDL.h>
#if (USE_SDL_FONT)
#include <SDL3_ttf/SDL_ttf.h>
#endif
#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#endif


Libraries::Libraries() {
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        logImportant("Can't load main library: %s", SDL_GetError());
    }

    // Initialasing font library
    #if (USE_SDL_FONT)
    if (!TTF_Init()) {
        logImportant("Can't load font library: %s", SDL_GetError());
    }
    #endif
    logAdditional("Libraries load correctly");
}

Libraries::~Libraries() noexcept {
    // Closing trueTypeFont library
    #if (USE_SDL_FONT)
    TTF_Quit();
    #endif

    // Closing main SDL library
    SDL_Quit();
}
