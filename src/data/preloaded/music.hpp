/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/dataLoader.hpp"


// Class for play music
template <unsigned count>
class MusicData {
 private:
    Mix_Music* music[count];
    Uint8 volume = 0;
    void loadMusic(const DataLoader& loader, unsigned index, const char* name);

 public:
    MusicData(const DataLoader& loader, const char* names[count]);
    ~MusicData();
    void start(unsigned name) const;
    void setVolume(unsigned volume);
    unsigned getVolume() const;
};
