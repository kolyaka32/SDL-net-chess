/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


// Names of music tracks
enum MUS_names{
    MUS_MENU_THEME,    // Music for menu
    MUS_MAIN_1,        // Music of cycles (#1)
    MUS_MAIN_2,        // Music of cycles (#2)
    MUS_MAIN_3,        // Music of cycles (#3)
    MUS_SINGLEPLAYER,  // Special music for singleplayer mode

    // Global counter of all loaded sounds
    MUS_count,
};


// File names of the corresponding music
extern const char* musicFilesNames[MUS_count];
