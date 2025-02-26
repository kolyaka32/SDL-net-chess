/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/dataLoader.hpp"
#include "../musicNames.hpp"


// Class for play music
class Music {
private:
    Mix_Music* music[MUS_count];
    Uint8 volume = 0;
    void loadMusic(const DataLoader& loader, unsigned index, const char* name);
public:
    Music(const DataLoader& loader);
    ~Music();
    void start(MUS_names name) const;
    void setVolume(unsigned volume);
    unsigned getVolume() const;
};
