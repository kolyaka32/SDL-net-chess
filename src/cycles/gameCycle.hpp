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
    static Board board;     // Main game field
    static Uint8 endState;  // State of game (end)

    SurroundingLetters letters;  // Letters, that surround field

    // GUI objects
    GUI::TextButton restartButton;
    GUI::TextButton menuButton;

    // Current game states
    GUI::StaticText playersTurnsTexts[4];

    // Ending options
    GUI::Backplate endBackplate;
    GUI::StaticText winText;
    GUI::StaticText firstWinText;
    GUI::StaticText secondWinText;
    GUI::StaticText looseText;
    GUI::StaticText nobodyWinText;

    // New overrided cycle functions
    void inputMouseDown(App& app) override;
    void inputKeys(App& app, const SDL_Keycode key) override;
    void draw(const App& app) const override;

 public:
    GameCycle(const App& app);
};
