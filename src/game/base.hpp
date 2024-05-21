/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/baseGUI.hpp"
#include "../cycleTemplate.hpp"
#include "entity/board.hpp"
#include "entity/letters.hpp"


// Cycle with game template
class GameCycle : public CycleTemplate {
 protected:
    Board board;  // Main game field
    Uint8 endState;  // State of game (end)

    // Extra UI
    SurroundingLetters letters;  // Letters, that surround field

    // GUI objects
    // Button for quit settings menu
    // GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};
    // Ending options
    GUI::Backplate endBackplate{{70, 150, SCREEN_WIDTH - 140, SCREEN_HEIGHT - 300}, 40, 5};

    // New overrided cycle functions
    bool getMouseInput() override;    // Getting mouse clicking
    bool getKeysInput(SDL_Keysym& key) override;  // Getting keys pressing
    void draw() const override;       // Drawing all needed objects

 public:
    GameCycle();   // Start game cycle
    ~GameCycle();  // Close game cycle
};
