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

    // Check, if figure at pos can be attacked
    inline bool isAttackable(Uint8 pos);
    // Set points, where you can move or attck
    inline void tryMove(Sint8 X, Sint8 Y);       
    inline void tryAttack(Sint8 X, Sint8 Y);      
    inline void setDiagonals(const coord _x, const coord _y);     // 
    inline void setStraight(const coord _x, const coord _y);      // 
    inline void setAround(const coord _x, const coord _y, const Sint8 pos[][2]);  // 
    
public:
    Board();
    ~Board();
    void reset();
    void blit() const;
    void click(const coord X, const coord Y);
};
