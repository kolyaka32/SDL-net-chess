/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_TEXTURES)

// Names of all images with related numbers
enum class Textures : unsigned {
    // Base part
    // Graphic interface sprites
    SliderButton,
    SliderLine,
    QuitButton,
    MenuButton,
    SaveButton,
    SettingsButton,

    // Base flags in settings
    FlagUSA,
    FlagRUS,
    FlagGER,
    FlagBEL,

    // Main game part
    // White figures
    WhitePawn,
    WhiteBishop,
    WhiteRook,
    WhiteKnight,
    WhiteQueen,
    WhiteKing,

    // Black figures
    BlackPawn,
    BlackBishop,
    BlackRook,
    BlackKnight,
    BlackQueen,
    BlackKing,

    // Point, where figure can go
    PointToMove,

    // Global counter of all textures
    Count,
};

// File names of the corresponding textures
extern const char* texturesFilesNames[unsigned(Textures::Count)];

// Operators for change textures depend on offset
Textures operator+(const Textures index, int offset);
Textures operator-(const Textures index, int offset);

#endif  // (PRELOAD_TEXTURES)
