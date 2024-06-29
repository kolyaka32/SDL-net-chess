/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "audio.hpp"


// Initialasing audio library
AudioLibrary::AudioLibrary() {
    // Initializing all audio library
    if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("audio library");
        #endif
    }

    // Openning audio chanel
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("audio chanel initialisation");
        #endif
    }
}

// Closing audio library
AudioLibrary::~AudioLibrary() {
    // Closing audio chanel
    Mix_CloseAudio();

    // Closing audio library
    Mix_Quit();
}
