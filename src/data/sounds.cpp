/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "sounds.hpp"


Sounds::Sounds(const DataLoader& _loader) {
    // Resetting all sounds
    #if CHECK_CORRECTION
    for (unsigned i=0; i < SND_count; ++i) {
        sounds[i] = nullptr;
    }
    #endif

    // Loading all needed sounds
    for (unsigned i=0; i < SND_count; ++i) {
        loadSound(_loader, i, soundsFilesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < SND_count; ++i) {
        if (sounds[i] == NULL) {
            throw DataLoadException("Sound with name: " + std::string(soundsFilesNames[i]));
        }
    }
    #endif
    
    // Resetting sounds volume
    setVolume(MIX_MAX_VOLUME/2);
}

Sounds::~Sounds() {
    // Closing all sounds
    for (unsigned i=0; i < SND_count; ++i) {
        Mix_FreeChunk(sounds[i]);
    }
}

void Sounds::loadSound(const DataLoader& _loader, unsigned _index, const char* _name) {
    // Load data of current sound
    SDL_IOStream* iodata = _loader.load(_name);

    // Creating surface
    sounds[_index] = Mix_LoadWAV_IO(iodata, true);

    // Checking correction of loaded sound
    #if CHECK_CORRECTION
    if (sounds[_index] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif
}

void Sounds::play(SND_names _index) const {
    Mix_PlayChannel(_index, sounds[_index], 0);
}

void Sounds::setVolume(unsigned _volume) {
    // Checking correction given volume
    #if CHECK_CORRECTION
    if (_volume > MIX_MAX_VOLUME) {
        throw "Wrong volume";
    }
    #endif
    volume = _volume;
    for (int i=0; i < SND_count; ++i) {
        Mix_VolumeChunk(sounds[i], volume);
    }
}

unsigned Sounds::getVolume() const {
    return volume;
}
