/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "figuresMoves.hpp"
#include "../GUI/interface.hpp"


// Configuration of board, for play
extern char boardConfig[85];

// Types of current game state
enum END_names {
    END_NONE,    // Nothing happen
    END_TURN,    // Flag of happened turn, equal to none
    END_WIN,     // Win of 1 or current player
    END_LOOSE,   // Win of 2 player or loose of current
    END_NOBODY,  // Nobody now can win
};


// Types of castling
enum CASTLING_names {
    CASTLING_W_K = 1,  // If castling possible for white from king side
    CASTLING_W_Q = 2,  // If castling possible for white from queen side
    CASTLING_B_K = 4,  // If castling possible for black from king side
    CASTLING_B_Q = 8,  // If castling possible for black from queen side
};


// Structure with current position
class Position {
public:
    Position(const Mouse mouse);
    Position(const position pos);
    Position(coord x, coord y);
    position getPosition();
    coord x, y;
};


// Class of game board to with
class Board : public FiguresMoves, public GUI::GUItemplate {
 private:
    Figure activeCell;     // Cell, that active (now move by player), or NULL if not
    Uint8 castling;        // Data of all now posible varhishes
    position endPosition;  // Postion, where end last move

    Uint8 click(const Sounds& sounds, Position pos);        // Clicking with mouse on cell on field
    void pickFigure(Position pos);                          // Function for pick figure from field
    Uint8 placeFigure(const Sounds& sounds, Position pos);  // Function to try put figure back to field
    SDL_FRect getRect(Position pos) const;

 public:
    void reset();                                     // Resetting field for new game
    void blit(const Window& target) const override;   // Bliting field at screen
    Uint8 click(const Sounds& sounds, const Mouse mouse);  // Clicking with mouse on cell on field
    void resetSelection();                                 // Reset currently selected figure

    // Simplier mover on field (for internet opponent turn)
    Uint8 move(const Sounds& sounds, Position p1, Position p2);
    position getLastTurnStart() const;  // Return start position in last turn
    position getLastTurnEnd() const;    // Return end position in last turn
    Uint8 currentTurn() const;          // Return, which person is now active
    bool isFigureSelected() const;      // Returns, if any figures now selected
};
