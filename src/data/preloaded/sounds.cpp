/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "sounds.hpp"


template <unsigned count>
SoundsData<count>::SoundsData(const DataLoader& _loader, const char* _names[count]) {
    // Resetting all sounds
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        sounds[i] = nullptr;
    }
    #endif

    // Loading all needed sounds
    for (unsigned i=0; i < count; ++i) {
        loadSound(_loader, i, _names[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        if (sounds[i] == NULL) {
            throw DataLoadException("Not loaded: " + std::string(_names[i]));
        }
    }
    #endif
    
    // Resetting sounds volume
    setVolume(MIX_MAX_VOLUME/2);
}

template <unsigned count>
SoundsData<count>::~SoundsData() {
    // Closing all sounds
    for (unsigned i=0; i < count; ++i) {
        Mix_FreeChunk(sounds[i]);
    }
}

template <unsigned count>
void SoundsData<count>::loadSound(const DataLoader& _loader, unsigned _index, const char* _name) {
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

template <unsigned count>
void SoundsData<count>::play(unsigned _index) const {
    Mix_PlayChannel(_index, sounds[_index], 0);
}

template <unsigned count>
void SoundsData<count>::setVolume(unsigned _volume) {
    // Checking correction given volume
    #if CHECK_CORRECTION
    if (_volume/2 > MIX_MAX_VOLUME) {
        throw "Wrong volume";
    }
    #endif
    volume = _volume/2;
    for (int i=0; i < count; ++i) {
        Mix_VolumeChunk(sounds[i], volume);
    }
}

template <unsigned count>
unsigned SoundsData<count>::getVolume() const {
    return volume*2;
}
