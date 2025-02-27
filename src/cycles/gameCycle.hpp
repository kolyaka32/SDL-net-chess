/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/baseGUI.hpp"
#include "baseCycle.hpp"
#include "../game/board.hpp"
#include "../game/letters.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
   static Board board;  // Main game field
   Uint8 endState;      // State of game (end)

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
   void getMouseInput(App& app) override;
   void getKeysInput(App& app, const SDL_Keycode key) override;
   void update(App& app) override;
   void draw(const App& app) const override;

 public:
   GameCycle(const App& app);
};
