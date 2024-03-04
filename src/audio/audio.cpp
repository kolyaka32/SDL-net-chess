#include "../include.hpp"
#include "../process.hpp"
#include "audio.hpp"
#include "../workCodes.hpp"


AudioLibrary::AudioLibrary(){
    // Initializing all audio library
    if(!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)){
        printf("Couldn't initialize audio library: %d\n", Mix_GetError());
        exit(ERR_SDL_SND);
    }

    // Openning audio chanel
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){
        printf("Couldn't initialase audio chanel.\n");
        exit(ERR_INI_SND);
    }
}

AudioLibrary::~AudioLibrary(){
    // Closing audio chanel
    Mix_CloseAudio();

    // Closing audio library
    Mix_Quit();
}
