#pragma once

#include "audio.hpp"
#include "../dataLoader.hpp"

// Names of sound effects
enum SND_names{

};

#define SND_count 0


// Class of all loaded sounds for play
class Sounds : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader
{
private:
    Mix_Chunk *sounds[SND_count];  // Array of all sound effects

    // Load sound with need name
    void loadSound(char *name, SND_names num);

    // Check correction of loaded sounds
    #if CHECK_CORRECTION
    bool checkCorrection();
    #endif
public:
    Sounds();   // Loading all sounds
    ~Sounds();  // Clear all data
    void playSound(SND_names track);  // Play need sound
};
