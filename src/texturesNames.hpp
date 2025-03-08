/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Names of all images with related numbers
enum IMG_names : unsigned {
    // Base part
    // Graphic interface sprites
    IMG_GUI_PAUSE_BUTTON,
    IMG_GUI_QUIT_BUTTON,
    IMG_GUI_SLIDER_BUTTON,
    IMG_GUI_SLIDER_LINE,
    IMG_GUI_TYPE_BOX,

    // Base flags in settings
    IMG_GUI_FLAG_USA,
    IMG_GUI_FLAG_RUS,
    IMG_GUI_FLAG_GER,
    IMG_GUI_FLAG_BEL,

    // Main game part
    // White figures
    IMG_GAME_WHITE_PAWN,
    IMG_GAME_WHITE_BISHOP,
    IMG_GAME_WHITE_ROOK,
    IMG_GAME_WHITE_KNIGHT,
    IMG_GAME_WHITE_QUEEN,
    IMG_GAME_WHITE_KING,

    // Black figures
    IMG_GAME_BLACK_PAWN,
    IMG_GAME_BLACK_BISHOP,
    IMG_GAME_BLACK_ROOK,
    IMG_GAME_BLACK_KNIGHT,
    IMG_GAME_BLACK_QUEEN,
    IMG_GAME_BLACK_KING,

    // Point, where figure can go
    IMG_GAME_POINT_MOVE_TO,

    // Global counter of all textures
    IMG_count,
};


// File names of the corresponding textures
extern const char* texturesFilesNames[IMG_count];
