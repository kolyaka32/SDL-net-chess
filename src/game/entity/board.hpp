#pragma once

#include "figures.hpp"

//
enum TURN_names{
    TURN_WHITE,
    TURN_BLACK,
};


// Class of game board to with
class Board
{
private:
    const static Uint8 fieldSize = sqr(FIELD_WIDTH);  // Size of all game field
    cell figures[fieldSize];                          // Array of figures on field
    TURN_names turn;                                  // Which player is currently turn
public:
    Board();
    ~Board();
    void reset();
    void blit() const;
    void click(coord X, coord Y);
};
