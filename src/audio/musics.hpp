#pragma once

#include "../include.hpp"
#include "../dataTypes.hpp"
#include "../dataLoader.hpp"
#include "audio.hpp"

// Names of all music tracks
enum MUS_names{

};

#define MUS_count 0


//
class Musics : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader
{
private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music

    void loadMusic(char* name, MUS_names num);
    bool checkCorrection();
public:
    Musics();
    ~Musics();
    void playMusic(MUS_names track);
};
