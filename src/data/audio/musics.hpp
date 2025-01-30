/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "audio.hpp"
#include "../dataLoader.hpp"

// Names of all music tracks
enum MUS_names{
    MUS_START_NONE,  // Track to not start new music

    MUS_MENU_THEME,  // Music for menu
    MUS_MAIN_1,      // Music of cycles (#1)
    MUS_MAIN_2,      // Music of cycles (#2)
    MUS_MAIN_3,      // Music of cycles (#3)
    MUS_SINGLEPLAYER,  // Special music for singleplayer mode
};

// Total counter of music (without NONE)
#define MUS_count 5
#define MUS_MAIN_count 3


// Class of all loaded music tracks for play
class Musics : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader {
 private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music

    // Load track with need name
    void loadMusic(const std::string name, const MUS_names num);

    // Check correction of loaded tracks
    #if CHECK_CORRECTION
    void checkCorrection();
    #endif

 public:
    Musics();   // Load all tracks
    ~Musics();  // Clear all data
    void playMusic(Uint8 track, int times = -1);  // Play need track need times
};
