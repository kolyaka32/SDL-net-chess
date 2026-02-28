/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_MUSIC)

// Names of music tracks
enum class Music {
    // Menu part
    Menu,

    // Game part
    Main,          // Music of cycles game
    Singleplayer,  // Special music for singleplayer mode

    // Global counter of all loaded sounds
    Count,
};

// File names of the corresponding music
extern const char* musicFilesNames[unsigned(Music::Count)];

#endif  // (PRELOAD_MUSIC)
