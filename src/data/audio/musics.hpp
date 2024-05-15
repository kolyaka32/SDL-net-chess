#pragma once

#include "audio.hpp"
#include "../dataLoader.hpp"

// Names of all music tracks
enum MUS_names{
    MUS_START_NONE,  // Track to not start new music

    MUS_MAIN_THEME,  // Main music for game cycles
    MUS_MENU_THEME,  // Music for menu
};

// Total counter of music (without NONE)
#define MUS_count 2


// Class of all loaded music tracks for play
class Musics : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader {
 private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music

    // Load track with need name
    void loadMusic(const char* name, const MUS_names num);

    // Check correction of loaded tracks
    #if CHECK_CORRECTION
    void checkCorrection();
    #endif

 public:
    Musics();   // Load all tracks
    ~Musics();  // Clear all data
    void playMusic(MUS_names track);  // Play need music track
};
