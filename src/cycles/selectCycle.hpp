/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../GUI/baseGUI.hpp"
#include "../game/background.hpp"

// Cycle for select variants to start
class SelectCycle : public BaseCycle {
 private:
   MovingBackground background;

   // GUI objects
   GUI::StaticText titleText{"Chess\0Шахматы\0Schach\0Шахматы",
      30, 0.5, 0.1, WHITE};
   GUI::TextButton singleplayerButton{"Singleplayer\0Одиночная игра\0Einzelspiel\0Адзіночная гульня",
      24, 0.5, 0.3, WHITE};
   GUI::TextButton twoPlayerButton{"Two players\0Два игрока\0Zwei Spieler\0Два гульца",
      24, 0.5, 0.5, WHITE};
   GUI::TextButton serverButton{"Create server\0Создать сервер\0Server erstellen\0Стварыць сервер",
      24, 0.5, 0.7, WHITE};
   GUI::TextButton connectButton{"Connect\0Присоединиться\0Beitreten\0Далучыцца",
      24, 0.5, 0.9, WHITE};

   // New overrided cycle functions
   bool getMouseInput() override;
   bool getKeysInput(const SDL_Keysym& key) override;
   void update() override;
   void draw() const override;

 public:
   SelectCycle();  // Create selecting cycle
};
