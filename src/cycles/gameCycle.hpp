/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/board.hpp"
#include "../game/letters.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    static Board board;     // Main game field
    static Uint8 endState;  // State of game (end)
    
    SurroundingLetters letters;  // Letters, that surround field
    const GUI::ImageButton gameRestartButton;  // Button for restart game
    GUI::StaticText playersTurnsTexts[2];

    // Menu after game end
    GUI::TextButton menuRestartButton;
    GUI::TextButton menuExitButton;
    GUI::Backplate menuBackplate;
    // Ending options
    GUI::StaticText firstWinText;
    GUI::StaticText secondWinText;
    GUI::StaticText nobodyWinText;

    // New overrided cycle functions
    void inputMouseDown(App& app) override;
    void inputKeys(App& app, const SDL_Keycode key) override;
    void draw(const App& app) const override;

 public:
    GameCycle(const App& app);
};
