/*
 * Copyright (C) 2024, Kazankov Nikolay 
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
    Board board;     // Main game field
    Uint8 endState;  // State of game (end)

    // Extra UI
    SurroundingLetters letters;  // Letters, that surround field

    // GUI objects
    GUI::TextButton restartButton{"Restart\0Перезапустить\0Starten\0Перазапуск",
       24, 0.5, 0.5, WHITE};
    GUI::TextButton menuButton{"Exit to menu\0Выйти в меню\0-\0-",
       24, 0.5, 0.6, WHITE};

    // Current game states
    GUI::StaticText playersTurnsTexts[4]{
      {"First player turn\0Ход первого игрока\0Der Zug des ersten Spielers\0Ход першага гульца",
         24, 0.5, 0.1, WHITE},
      {"Second player turn\0Ход второго игрока\0Zug des zweiten Spielers\0Ход другога гульца",
         24, 0.5, 0.1, WHITE},
      {"Your turn\0Ваш ход\0Sie spielen aus\0Ваш ход",
         24, 0.5, 0.1, WHITE},
      {"Wait\0Ожидайте\0Erwartet\0Чакаць",
         24, 0.5, 0.1, WHITE}
    };

    // Ending options
    GUI::Backplate endBackplate{{70, 150, SCREEN_WIDTH - 140, SCREEN_HEIGHT - 300}, 40, 5};
    GUI::StaticText winText{"Win!\0Победа!\0Sieg!\0Перамога!",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText firstWinText{"Fist player win!\0Первый игрок выйграл!\0Der erste Spieler hat gewonnen!\0Першы гулец выйграў!",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText secondWinText{"Second player win!\0Второй игрок выйграл!\0Der zweite Spieler hat gewonnen!\0Другі гулец выйграў!",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText looseText{"You loose...\0Вы проиграли...\0Sie haben verloren...\0Вы прайгралі...",
       30, 0.5, 0.4, WHITE};
    GUI::StaticText nobodyWinText{"Nobody win\0Ничья\0Unentschieden\0Чые",
       30, 0.5, 0.4, WHITE};

    // Button for quit settings menu
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};
    GUI::ImageButton exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};

    // New overrided cycle functions
    bool getMouseInput() override;
    bool getKeysInput(const SDL_Keysym& key) override;
    void draw() const override;

 public:
    GameCycle();
    ~GameCycle();
};
