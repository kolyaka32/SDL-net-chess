#pragma once

#include "figures.hpp"

// Types of which player is active
enum TURN_names{
    TURN_WHITE,
    TURN_BLACK,
};

// Types of current game state
enum END_names{
    END_NONE,    // Nothing happen
    END_TURN,    // Flag of happened turn, equal to none
    END_WIN,     // Win of 1 or current player
    END_LOOSE,   // Win of 2 player or loose of current
    END_NOBODY,  // Nobody now can win
};

// Types of castling
enum CASTLING_names{
    CASTLING_W_K = 1,  // If castling possible for white from king side
    CASTLING_W_Q = 2,  // If castling possible for white from queen side
    CASTLING_B_K = 4,  // If castling possible for black from king side
    CASTLING_B_Q = 8,  // If castling possible for black from queen side
};

// Class of game board to with
class Board
{
private:
    const static Uint8 fieldSize = sqr(FIELD_WIDTH);  // Size of all game field
    cell figures[fieldSize];                          // Array of figures on field
    bool turn;                                        // Which player is currently turn
    Figure activeCell;                                // Cell, that active (now move by player), or NULL if not
    bool wasMoven;                                    // Flag of board, that it was moven
    Uint8 castling;                                    // Data of all now posible varhishes

    // Check, if figure at pos can be attacked
    bool isAttackable(const position pos);
    bool tryMoveTo(const position pos);
    // Set points, where you can move or attck
    void tryMove(Sint8 X, Sint8 Y);
    void tryAttack(Sint8 X, Sint8 Y);
    void setDiagonals(const coord _x, const coord _y);
    void setStraight(const coord _x, const coord _y);
    void setAround(const coord _x, const coord _y, const Sint8 pos[][2]);
    void setCastlingLeft(const coord _x, const coord _y, const cell need);
    void setCastlingRight(const coord _x, const coord _y, const cell need);
    
public:
    Board();
    ~Board();
    void reset();  // Resetting field for new game
    void blit() const;  // Bliting field at screen
    Uint8 click(const coord X, const coord Y);  // Clicking with mouse on need cell on field
    Uint8 move(const coord X1, const coord Y1, const coord X2, const coord Y2);  // Simplier mover on field (for internet opponent turn)
    position getPreviousTurn();  // Return, where was made previous turn
};
