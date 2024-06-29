/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "sounds.hpp"

// Sound class
// Loading all sounds
Sounds::Sounds() {
    // Resetting list of sounds
    #if CHECK_CORRECTION
    memset(sounds, 0, SND_count * sizeof(*sounds));
    #endif

    // Loading all sounds
    // loadSound("snd/.wav", SND_);  // Template

    loadSound("turn.wav", SND_TURN);
    loadSound("reset.wav", SND_RESET);

    // Checking correction of loading
    #if CHECK_CORRECTION
    checkCorrection();
    #endif

    // Setting start volume of effects
    Mix_Volume(-1, soundsVolume);
}

// Clearing all musics after work
Sounds::~Sounds() {
    for (int i=0; i < SND_count; ++i) {
        Mix_FreeChunk(sounds[i]);
    }
}

// Play need sound
void Sounds::playSound(const SND_names _index) {
    Mix_PlayChannel(-1, sounds[_index], 0);
}

// Load sound with need name
void Sounds::loadSound(const std::string _name, const SND_names _index) {
    // Getting selected file data
    SDL_RWops *tempRW = loadObject("snd/" + _name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if (tempRW == nullptr) {
        throw DataLoadException("sound file: " + _name);
    }
    #endif

    // Creating sound, setting in array and clearing data
    sounds[_index] = Mix_LoadWAV_RW(tempRW, 0);

    // Freeing data from sound
    // free(tempRW->hidden.mem.base);
    SDL_RWclose(tempRW);

    // Checking correction of loaded sound
    #if CHECK_CORRECTION
    if (sounds[_index] == nullptr) {
        throw DataLoadException("sound file: " + _name);
    }
    #endif
}

// Check correction of loaded sounds
#if CHECK_CORRECTION
void Sounds::checkCorrection() {
    // Checking, if all sounds exist
    for (Uint8 i = 0; i < SND_count; ++i) {
        if (sounds[i] == NULL) {
            throw DataLoadException("sound file count");
        }
    }
}
#endif
