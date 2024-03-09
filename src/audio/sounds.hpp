#pragma once

#include "../include.hpp"
#include "../dataTypes.hpp"
#include "../dataLoader.hpp"
#include "audio.hpp"

// Names of sound effects
enum SND_names{

};

#define SND_count 0


//
class Sounds : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader
{
private:
    Mix_Chunk *sounds[SND_count];      // Array of all sound effects

    void loadSound(char *name, SND_names num);
    bool checkCorrection();
public:
    Sounds();
    ~Sounds();
    void playSound(SND_names track);
};
