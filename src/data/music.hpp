/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "SDL_mixer.h"
#include "loader/dataLoader.hpp"
#include "../musicNames.hpp"


// Class for play music
class Music
{
private:
    Mix_Music* music[MUS_count];
    void loadMusic();
public:
    Music(const DataLoader& loader);
    ~Music();
    void playMusic(MUS_names name);
};
