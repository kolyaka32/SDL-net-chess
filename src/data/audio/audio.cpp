#include "audio.hpp"


// Initialasing audio library
AudioLibrary::AudioLibrary() {
    // Initializing all audio library
    if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)) {
        #if CHECK_CORRECTION
        SDL_Log("Couldn't initialize audio library: %d\n", Mix_GetError());
        exit(ERR_SDL_SND);
        #endif
    }

    // Openning audio chanel
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
        #if CHECK_CORRECTION
        SDL_Log("Couldn't initialase audio chanel.\n");
        exit(ERR_INI_SND);
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
