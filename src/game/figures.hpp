/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"
#include "SDL3/SDL_stdinc.h"

typedef Uint8 cell;
typedef Uint8 position;
typedef Uint8 coord;

// Names of all figures in game
enum FIG_names {
    // None-element
    FIG_NONE,

    // Figures
    // White figures
    FIG_WHITE_PAWN,
    FIG_WHITE_BISHOP,
    FIG_WHITE_ROOK,
    FIG_WHITE_KNIGHT,
    FIG_WHITE_QUEEN,
    FIG_WHITE_KING,

    // Black figures
    FIG_BLACK_PAWN,
    FIG_BLACK_BISHOP,
    FIG_BLACK_ROOK,
    FIG_BLACK_KNIGHT,
    FIG_BLACK_QUEEN,
    FIG_BLACK_KING,

    // Point, where you can move to
    FIG_MOVE_TO,
};

// Macros for getting position from coordinats
#define getPos(x, y) ((x) + (y) * FIELD_WIDTH)


// Extra names modifires
#define FIG_RED_TYPE 0x10   // Code of making cell red (attackable)
#define FIG_BLUE_TYPE 0x20  // Code of making cell blue (current)


// Type of cell
struct Figure {
    cell type;  // Type of current cell
    position pos;   // Coordinats of current cell
};

// Array of king possible ways to go
const Sint8 kingMoves[8][2] = {
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1}
};

// Array of possible knight ways to go
const Sint8 knightMoves[8][2] = {
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1},
    {-2, 1}
};
