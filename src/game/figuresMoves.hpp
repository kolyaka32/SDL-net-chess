/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "figures.hpp"


// Types of which player is active
enum TURN_names{
    TURN_WHITE,
    TURN_BLACK,
};


// Interface of figures moves
class FiguresMoves {
 protected:
    // Data for moves
    cell figures[sqr(FIELD_WIDTH)];  // Array of figures on field
    bool turn;                       // Which player is currently turn
    bool wasMoven;                   // Flag of board, that it was moven
    void resetField();               // Reset field parametrs

    // Functions for interact with board
    // Check, if figure at pos can be attacked
    bool isAttackable(position pos);
    bool tryMoveTo(position pos);
    // Set points, where you can move or attack
    void tryMove(Sint8 X, Sint8 Y);
    void tryAttack(Sint8 X, Sint8 Y);
    void setDiagonals(coord _x, coord _y);
    void setStraight(coord _x, coord _y);
    void setAround(coord _x, coord _y, const Sint8 pos[][2]);
    void setCastlingLeft(coord _x, coord _y, cell need);
    void setCastlingRight(coord _x, coord _y, cell need);

 public:
    FiguresMoves();
};
