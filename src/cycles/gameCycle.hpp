/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/gameBoard.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    GameBoard board;  // Main game field
    //static Uint8 endState;  // State of game (end)
    SurroundingLetters letters;  // Letters, that surround field

    // Save options
    GUI::ImageButton gameSaveButton;
    GUI::ImageButton gameMenuButton;
    GUI::InfoBox savedInfo;
    //const GUI::ImageButton gameRestartButton;  // Button for restart game

    // Current turn texts
    GUI::StaticText playersTurnsTexts[2];

    // Ending options
    GUI::StaticText firstWinText;
    GUI::StaticText secondWinText;
    GUI::StaticText nobodyWinText;

 protected:
    void inputKeys(const SDL_Keycode key) override;
    void update() override;

 public:
    GameCycle(Window& window);
};
