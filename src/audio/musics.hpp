#pragma once

#include "../include.hpp"
#include "../dataTypes.hpp"
#include "audio.hpp"

// Names of all music tracks
enum MUS_names{

};

#define MUS_count 0

class Musics : AudioLibrary
{
private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music

    count loadAllMusic();
    void loadMusic(char* name, MUS_names num);
public:
    Musics();
    ~Musics();
    void playMusic(MUS_names track);
};
