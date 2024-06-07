/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cycleTemplate.hpp"
#include "GUI/baseGUI.hpp"


// Cycle for select variants to start
class SelectCycle : public CycleTemplate {
 private:
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

    // Setting menu button
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    bool getMouseInput() override;   // Checking for any need mouse action
    bool getKeysInput(SDL_Keysym& key) override;  // Checking for any keys actions
    void draw() const override;      // Drawing all needed objects

 public:
    SelectCycle();   // Create selecting cycle
};
