/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "board.hpp"
#include "letters.hpp"


// Class for interaction with whole game
class GameBoard : public GUI::Template {
 protected:
    // Current game board for interaction
    static Board board;
    // Additional graphic part
    SurroundingLetters letters;

 public:
    GameBoard(const Window& window);

    // Setting field for play
    void setNewField(const Field& field);

    // Main interaction with game (depend on game mode)
    // Clicking with mouse on cell on field
    // void clickSingle(const Mouse mouse);
    void clickCooperative(const Mouse mouse);
    void clickServer(const Mouse mouse);
    void clickClient(const Mouse mouse);
    // Reseting currently selected figure
    void resetSelection();

    void blit() const override;
};
