/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "audio.hpp"
#include "../dataLoader.hpp"

// Names of sound effects
enum SND_names{
    SND_TURN,   // Sound of player's turn
    SND_RESET,  // Sound of field reset
};

// Total counter of sounds
#define SND_count 2


// Class of all loaded sounds for play
class Sounds : virtual AudioLibrary, public virtual InitFile, public virtual DataLoader {
 private:
    Mix_Chunk *sounds[SND_count];  // Array of all sound effects

    // Load sound with need name
    void loadSound(const std::string name, const SND_names index);

    // Check correction of loaded sounds
    #if CHECK_CORRECTION
    void checkCorrection();
    #endif

 public:
    Sounds();   // Loading all sounds
    ~Sounds();  // Clear all data
    void playSound(const SND_names track);  // Play need sound
};
