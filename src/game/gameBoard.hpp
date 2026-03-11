/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "figuresMoves.hpp"
#include "../GUI/interface.hpp"


// Configuration of board, for play
//extern char boardConfig[85];


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
class Board : public FiguresMoves, public GUI::Template {
 private:
    Figure activeCell;     // Cell, that active (now move by player), or NULL if not
    position endPosition;  // Postion, where end last move
    const SDL_FRect rect;  // Global position of board

    Uint8 click(Position pos);        // Clicking with mouse on cell on field
    void pickFigure(Position pos);    // Function for pick figure from field
    Uint8 placeFigure(Position pos);  // Function to try put figure back to field
    SDL_FRect getRect(Position pos) const;

 public:
    Board(const Window& window);
    void reset();                // Resetting field for new game
    void blit() const override;  // Bliting field at screen
    Uint8 click(const Mouse mouse);  // Clicking with mouse on cell on field
    void resetSelection();       // Reset currently selected figure

    // Simplier mover on field (for internet opponent turn)
    Uint8 move(Position p1, Position p2);
    position getLastTurnStart() const;  // Return start position in last turn
    position getLastTurnEnd() const;    // Return end position in last turn
    Uint8 currentTurn() const;          // Return, which person is now active
    bool isFigureSelected() const;      // Returns, if any figures now selected
};
