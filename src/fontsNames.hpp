/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/preloaded/fonts.cpp"


// Names of fonts
enum FNT_names{
    FNT_MAIN,    // Main using font (now only one)

    // Global counter of all loaded fonts
    FNT_count,
};

// Shortcut for font data class
typedef FontsData<FNT_count> Fonts;

// File names of the corresponding fonts
extern const char* fontsFilesNames[FNT_count];
