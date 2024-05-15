#pragma once

#include "figuresMoves.hpp"


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
class Board : public FiguresMoves {
 private:
    Figure activeCell;  // Cell, that active (now move by player), or NULL if not
    Uint8 castling;     // Data of all now posible varhishes

    void pickFigure(const coord X, const coord Y);    // Function for pick figure from field
    Uint8 placeFigure(const coord X, const coord Y);  // Function to try put figure back to field

 public:
    Board();
    ~Board();
    void reset();  // Resetting field for new game
    void blit() const;  // Bliting field at screen
    Uint8 click(const coord X, const coord Y);  // Clicking with mouse on need cell on field
    // Simplier mover on field (for internet opponent turn)
    Uint8 move(const coord X1, const coord Y1, const coord X2, const coord Y2);
    void resetSelection();  // Reset currently selected figure
    position getPreviousTurn() const;  // Return, where was made previous turn
    Uint8 currentTurn() const;         // Return, which person is now active
};
