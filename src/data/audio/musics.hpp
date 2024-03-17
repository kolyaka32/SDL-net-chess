#pragma once

#include "audio.hpp"
#include "../dataLoader.hpp"

// Names of all music tracks
enum MUS_names{

};

#define MUS_count 0


// Class of all loaded music tracks for play
class Musics : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader
{
private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music

    // Load track with need name
    void loadMusic(char* name, MUS_names num);
    
    // Check correction of loaded tracks
    #if CHECK_CORRECTION
    bool checkCorrection();
    #endif
public:
    Musics();   // Load all tracks
    ~Musics();  // Clear all data
    void playMusic(MUS_names track);  // Play need music track
};
