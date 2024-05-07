#pragma once

#include "figures.hpp"


// Types of which player is active
enum TURN_names{
    TURN_WHITE,
    TURN_BLACK,
};


// Interface of figures moves
class FiguresMoves
{
protected:
    // Data for moves
    cell figures[sqr(FIELD_WIDTH)];   // Array of figures on field
    bool turn;                        // Which player is currently turn
    bool wasMoven;                    // Flag of board, that it was moven

    // Check, if figure at pos can be attacked
    bool isAttackable(const position pos);
    bool tryMoveTo(const position pos);
    // Set points, where you can move or attack
    void tryMove(Sint8 X, Sint8 Y);
    void tryAttack(Sint8 X, Sint8 Y);
    void setDiagonals(const coord _x, const coord _y);
    void setStraight(const coord _x, const coord _y);
    void setAround(const coord _x, const coord _y, const Sint8 pos[][2]);
    void setCastlingLeft(const coord _x, const coord _y, const cell need);
    void setCastlingRight(const coord _x, const coord _y, const cell need);
public:
    FiguresMoves();
};
