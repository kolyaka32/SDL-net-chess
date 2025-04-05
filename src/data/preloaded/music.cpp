/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "music.hpp"


template <unsigned count>
MusicData<count>::MusicData(const DataLoader& _loader, const char* _names[count]){
    // Resetting all tracks
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        music[i] = nullptr;
    }
    #endif

    // Loading all needed music tracks
    for (unsigned i=0; i < count; ++i) {
        loadMusic(_loader, i, _names[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        if (music[i] == NULL) {
            throw DataLoadException("Music with name: " + std::string(_names[i]));
        }
    }
    #endif

    // Resetting music volume
    setVolume(MIX_MAX_VOLUME/2);
}

template <unsigned count>
MusicData<count>::~MusicData(){
    // Closing all tracks
    for (unsigned i=0; i < count; ++i) {
        Mix_FreeMusic(music[i]);
    }
}

template <unsigned count>
void MusicData<count>::loadMusic(const DataLoader& _loader, unsigned _index, const char* _name) {
    // Load data of current music track
    SDL_IOStream* iodata = _loader.load(_name);

    // Loading track
    music[_index] = Mix_LoadMUS_IO(iodata, true);

    // Checking correction of loaded track
    #if CHECK_CORRECTION
    if (music[_index] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif
}

template <unsigned count>
void MusicData<count>::start(unsigned _index) const {
    // Infinite playing selected music
    Mix_PlayMusic(music[_index], -1);
}

template <unsigned count>
void MusicData<count>::setVolume(unsigned _volume) {
    // Checking correction given volume
    #if CHECK_CORRECTION
    if (_volume/2 > MIX_MAX_VOLUME) {
        throw "Wrong volume";
    }
    #endif
    volume = _volume/2;
    Mix_VolumeMusic(volume);
}

template <unsigned count>
unsigned MusicData<count>::getVolume() const {
    return volume*2;
}
