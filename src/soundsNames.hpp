/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/sounds.cpp"

// Names of sound effects
enum SND_names{
    SND_TURN,   // Sound of player's turn
    SND_RESET,  // Sound of field reset

    // Global counter of all loaded sounds
    SND_count,
};

// Shortcut for sounds data class
typedef SoundsData<SND_count> Sounds;

// File names of the corresponding sounds
extern const char* soundsFilesNames[SND_count];
