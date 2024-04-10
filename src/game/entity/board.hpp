#pragma once

#include "figures.hpp"

// Types of which player is active
enum TURN_names{
    TURN_WHITE,
    TURN_BLACK,
};

// State of cell, that it not uses
#define CELL_INACTIVE 255


// Class of game board to with
class Board
{
private:
    const static Uint8 fieldSize = sqr(FIELD_WIDTH);  // Size of all game field
    Uint8 figures[fieldSize];                     // Array of figures on field
    Uint8 turn;                                  // Which player is currently turn
    Figure activeCell;                           // Cell, that active (now move by player), or NULL if not

    inline void tryMove(Sint8 X, Sint8 Y);       // Try set point, where you can move
    inline void setDiagonals(const coord _x, const coord _y);     // 
    inline void setStraight(const coord _x, const coord _y);      // 
    inline void setAroundKnight(const coord _x, const coord _y);  // 
    inline void setAroundKing(const coord _x, const coord _y);    // 
    
public:
    Board();
    ~Board();
    void reset();
    void blit() const;
    void click(const coord X, const coord Y);
};
