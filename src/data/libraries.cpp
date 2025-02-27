/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */


#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "exceptions.hpp"
#include "libraries.hpp"


Libraries::Libraries() {
    // Load depend on teting
    #if CHECK_CORRECTION
    // Initialasing main library
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        throw LibararyLoadException("Main library: " + std::string(SDL_GetError()));
    }
    // Initialasing font library
    if (!TTF_Init()) {
        throw LibararyLoadException("Font library: " + std::string(SDL_GetError()));
    }
    // Initialasing audio library
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK)) {
        throw LibararyLoadException("Mixer library: " + std::string(SDL_GetError()));
    }
    // Starting audio
    audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (audioDeviceID == 0) {
        throw LibararyLoadException("Couldn't get audio device ID: " + std::string(SDL_GetError()));
    }
    // Openning audio chanel
    if(!Mix_OpenAudio(audioDeviceID, NULL)){
        throw LibararyLoadException("Couldn't initialase audio chanel: " + std::string(SDL_GetError()));
    }
    #else
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
    audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    Mix_OpenAudio(audioDeviceID, NULL);
    #endif
}

Libraries::~Libraries() noexcept {
    // Closing audio device
    Mix_CloseAudio();
    SDL_CloseAudioDevice(audioDeviceID);

    // Closing all library reversed
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
