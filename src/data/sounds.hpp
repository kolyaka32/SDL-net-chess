/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include "loader/dataLoader.hpp"
#include "../soundsNames.hpp"


// Class for playing sound with need name
class Sounds {
private:
    Mix_Chunk* sounds[SND_count];
    Uint8 volume = 0;
    void loadSound(const DataLoader& loader, unsigned index, const char* name);
public:
    Sounds(const DataLoader& loader);
    ~Sounds();
    void play(SND_names name) const;
    void setVolume(unsigned _volume);
    unsigned getVolume() const;
};
