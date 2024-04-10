#pragma once

#include "../../define.hpp"
#include "../../dataTypes.hpp"

// Names of all figures in game
enum FIG_names{
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


// Type of cell
struct Figure
{
    Uint8 type;  // Type of current cell
    Sint8 X, Y;      // Coordinats of current cell
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
