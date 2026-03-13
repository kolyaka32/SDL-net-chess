/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "field.hpp"


// Structure with current position
class Position {
 public:
    Position(const Mouse mouse);
    Position(const position pos);
    Position(coord x, coord y);
    position getPosition();
    coord x, y;
};


// Class of game board (Field with graphic and midle level of interaction)
class Board : public Field {
 private:
    // Cell, that active (now move by player), or NULL if not selected
    cell activeCell;
    position activePosition;

    position endPosition;  // Postion, where end last move
    const SDL_FRect rect;  // Global position of board

    Uint8 click(Position pos);        // Clicking with mouse on cell on field
    void pickFigure(Position pos);    // Function for pick figure from field
    Uint8 placeFigure(Position pos);  // Function to try put figure back to field
    SDL_FRect getRect(Position pos) const;

 public:
    // Creating emplty starting field
    Board();
    // Setting new field
    Board& operator=(const Field& field);

    // Active game part
    // Getting current game state
    GameState getState();
    // Check, if position is valid game place
    bool isValid(const Mouse mouse);
    // Getting relative position in field coordiants
    position getPosition(const Mouse mouse);

    Uint8 click(const Mouse mouse);  // Clicking with mouse on cell on field
    void resetSelection();       // Reset currently selected figure

    // Bliting field at screen
    void blit(const Window& window) const;

    // Simplier mover on field (for internet opponent turn)
    //Uint8 move(Position p1, Position p2);
    //position getLastTurnStart() const;  // Return start position in last turn
    //position getLastTurnEnd() const;    // Return end position in last turn
    //Uint8 currentTurn() const;          // Return, which person is now active
    bool isFigureSelected() const;      // Returns, if any figures now selected
};
