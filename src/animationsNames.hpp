/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/animations.hpp"
#include "data/preloaded/animations.cpp"

// Names of gif animation
enum ANI_names{
    ANI_SINGLEPLAYER,  // Animation in singleplayer

    // Global counter of all loaded animations
    ANI_count,
};

// Shortcut for font data class
typedef AnimationsData<ANI_count> Animations;

// File names of the corresponding animations
extern const char* animationsFilesNames[ANI_count];
