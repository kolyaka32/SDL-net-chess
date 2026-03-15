/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "field.hpp"


// Class of game board (Field with graphic and midle level of interaction)
class Board : public Field {
 private:
    // Cell, that active (now move by player), or NULL if not selected
    cell activeCell;
    Position activePosition;

    position endPosition;  // Postion, where end last move
    const SDL_FRect rect;  // Global position of board

    Uint8 click(Position pos);       // Clicking with mouse on cell on field
    void pickFigure(Position pos);   // Function for pick figure from field
    void placeFigure(Position pos);  // Function to try put figure back to field

 protected:
    // Check, if position is valid game place
    bool isValid(const Mouse mouse);
    // Getting relative position in field coordiants
    Position getPosition(const Mouse mouse);

 public:
    // Creating empty field (for static start)
    Board();
    // Setting new field from loaded
    Board& operator=(const Field& field);

    // Active game part
    // Getting current game state
    GameState getState();

    // Main interaction with game (depend on game mode)
    // Clicking with mouse on cell on field
    // void clickSingle(const Mouse mouse);
    void clickCooperative(const Mouse mouse);
    void clickServer(const Mouse mouse);
    void clickClient(const Mouse mouse);
    // Reseting currently selected figure
    void resetSelection();

    // Bliting field at screen
    void blit(const Window& window) const;
};
