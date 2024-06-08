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
    GUI::TextButton restartButton{"Restart\0Перезапустить\0-\0-",
       24, 0.5, 0.5, WHITE};
    GUI::TextButton menuButton{"Exit to menu\0Выйти в меню\0-\0-",
       24, 0.5, 0.6, WHITE};

    // Current game states
    GUI::StaticText playersTurnsTexts[4]{
      {"First player turn\0Ход первого игрока\0-\0-",
         24, 0.5, 0.1, WHITE},
      {"Second player turn\0Ход второго игрока\0-\0-",
         24, 0.5, 0.1, WHITE},
      {"Your turn\0Ваш ход\0-\0-",
         24, 0.5, 0.1, WHITE},
      {"Wait\0Ожидайте\0-\0-",
         24, 0.5, 0.1, WHITE}
    };

    // Ending options
    GUI::Backplate endBackplate{{70, 150, SCREEN_WIDTH - 140, SCREEN_HEIGHT - 300}, 40, 5};
    GUI::StaticText winText{"Win!\0Победа!\0-\0",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText firstWinText{"Fist player win!\0Первый игрок выйграл!\0-\0-",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText secondWinText{"Second player win!\0Второй игрок выйграл!\0-\0-",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText looseText{"You loose...\0Вы проиграли...\0-\0-",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText nobodyWinText{"Nobody win\0Ничья\0-\0-",
       30, 0.5, 0.4, WHITE};

    // Button for quit settings menu
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};
    GUI::ImageButton exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};

    // New overrided cycle functions
    bool getMouseInput() override;    // Getting mouse clicking
    bool getKeysInput(SDL_Keysym& key) override;  // Getting keys pressing
    void draw() const override;       // Drawing all needed objects

 public:
    GameCycle();   // Start game cycle
    ~GameCycle();  // Close game cycle
};
