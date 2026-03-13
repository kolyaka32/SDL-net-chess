/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


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

// Extra cell modifires
#define FIG_RED_TYPE 0x10  // Code for making cell red (attackable)
#define CELL_TYPE_MASK 0xFF  // Mask for get type of cell

// Type for storing one cell (from FIG_names)
typedef Uint8 cell;
// Type for storing one-dimanional position
typedef Uint8 coord;
// Type for storing two-dimansinal position (get from getPos())
typedef Uint8 position;

// Macros for getting position from coordinats
#define getPos(x, y) ((((x)) + ((y)) * FIELD_WIDTH))

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
