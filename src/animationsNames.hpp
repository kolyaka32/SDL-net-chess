/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_ANIMATIONS)

// Names of gif animation
enum class Animations {
    // Game part
    SinglePlayer,  // Animation in singleplayer

    // Global counter of all loaded animations
    Count,
};

// File names of the corresponding animations
extern const char* animationsFilesNames[unsigned(Animations::Count)];

#endif  // (PRELOAD_ANIMATIONS)
