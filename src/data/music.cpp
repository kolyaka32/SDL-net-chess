/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "music.hpp"


Music::Music(const DataLoader& _loader){
    // Resetting all tracks
    #if CHECK_CORRECTION
    for (unsigned i=0; i < MUS_count; ++i) {
        music[i] = nullptr;
    }
    #endif

    // Loading all needed music tracks
    for (unsigned i=0; i < MUS_count; ++i) {
        loadMusic(_loader, i, musicFilesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < MUS_count; ++i) {
        if (music[i] == NULL) {
            throw DataLoadException("Music with name: " + std::string(musicFilesNames[i]));
        }
    }
    #endif

    // Resetting music volume
    setVolume(MIX_MAX_VOLUME/2);
}

Music::~Music(){
    // Closing all tracks
    for (unsigned i=0; i < MUS_count; ++i) {
        Mix_FreeMusic(music[i]);
    }
}

void Music::loadMusic(const DataLoader& _loader, unsigned _index, const char* _name) {
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

void Music::start(MUS_names _index) const {
    // Infinite playing selected music
    Mix_PlayMusic(music[_index], -1);
}

void Music::setVolume(unsigned _volume) {
    // Checking correction given volume
    #if CHECK_CORRECTION
    if (_volume > MIX_MAX_VOLUME) {
        throw "Wrong volume";
    }
    #endif
    volume = _volume;
    Mix_VolumeMusic(volume);
}

unsigned Music::getVolume() const {
    return volume;
}
