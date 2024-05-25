/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "initFile.hpp"
#include "../GUI/baseGUI.hpp"


// Types of language
enum LNG_types{
    LNG_ENGLISH,    // English language
    LNG_RUSSIAN,    // Russian language
    LNG_GERMAN,     // German language
    LNG_BELARUSIAN  // Belarusian language
};

#define LNG_count 4  // Final counter of all languages


// Types of numerated static texts
enum TXT_types{
    // Selection menu
    TXT_SELECT_TITLE,    // Game name
    TXT_SELECT_SINGLE,   // Singleplayer gamemode
    TXT_SELECT_TWO,      // Two player gamemode
    TXT_SELECT_SERVER,   // Host server
    TXT_SELECT_CLIENT,   // Connect to server

    // Pause menu
    TXT_PAUSE_TITLE,
    TXT_PAUSE_MUSIC,
    TXT_PAUSE_SOUND,

    // Game turnes
    // Turnes at one computer
    TXT_GAME_TURN_FIRST,
    TXT_GAME_TURN_SECOND,

    // Turnes at internet connection
    TXT_GAME_TURN_THIS,
    TXT_GAME_TURN_ANOTHER,

    // End game texts
    TXT_END_WIN,
    TXT_END_WIN_1,
    TXT_END_WIN_2,
    TXT_END_LOOSE,
    TXT_END_NOBODY,

    // Buttons texts
    TXT_BUTTON_RESTART,
    TXT_BUTTON_MENU,
    TXT_BUTTON_CONNECT,
    TXT_BUTTON_CANCEL,

    // Server texts
    TXT_SERVER_WAIT,
    TXT_SERVER_PORT,

    // Client texts
    TXT_CLIENT_ENTER_IP,
    TXT_CLIENT_ENTER_PORT,
};

// Summary texts counter
#define TXT_count 25


// Framed buttons
// Names of all framed text buttons
enum BTN_names{
    // Selection menu
    BTN_SELECT_SINGLE,   // Singleplayer gamemode
    BTN_SELECT_TWO,      // Two player gamemode
    BTN_SELECT_SERVER,   // Host server
    BTN_SELECT_CLIENT,   // Connect to server

    // Buttons texts
    BTN_GAME_RESTART,
    BTN_GAME_MENU,
    BTN_GAME_CONNECT,
    BTN_GAME_CANCEL,
};

// Counter of framed text buttons
#define BTN_count 8


// All static texts
class Texts : public virtual App, public virtual InitFile {
 public:
    // All static texts in game
    GUI::StaticText texts[TXT_count] = {
        // Selection menu
        {"Chess\0Шахматы\0Schach\0Шахматы",
            30, 0.5, 0.1, WHITE},
        {"Singleplayer\0Одиночная игра\0Einzelspiel\0Адзіночная гульня",
            24, 0.5, 0.3, WHITE},
        {"Two players\0Два игрока\0Zwei Spieler\0Два гульца",
            24, 0.5, 0.5, WHITE},
        {"Create server\0Создать сервер\0Server erstellen\0Стварыць сервер",
            24, 0.5, 0.7, WHITE},
        {"Connect\0Присоединиться\0Beitreten\0Далучыцца",
            24, 0.5, 0.9, WHITE},

        // Pause menu
        {"Pause\0Пауза\0Pause\0Паўза",
            30, 0.5, 0.1},
        {"Music\0Музыка\0Die Musik\0Музыка",
            30, 0.5, 0.68},
        {"Sounds\0Звуки\0Geräusche\0Гук",
            30, 0.5, 0.83},

        // Game turnes
        {"First player turn\0Ход первого игрока\0-\0-",
            24, 0.5, 0.1, WHITE},
        {"Second player turn\0Ход второго игрока\0-\0-",
            24, 0.5, 0.1, WHITE},
        {"Your turn\0Ваш ход\0-\0-",
            24, 0.5, 0.1, WHITE},
        {"Wait\0Ожидайте\0-\0-",
            24, 0.5, 0.1, WHITE},

        // Game end texts
        {"Win!\0Победа!\0-\0",
            30, 0.5, 0.4, WHITE},
        {"Fist player win!\0Первый игрок выйграл!\0-\0-",
            30, 0.5, 0.4, WHITE},
        {"Second player win!\0Второй игрок выйграл!\0-\0-",
            30, 0.5, 0.4, WHITE},
        {"You loose...\0Вы проиграли...\0-\0-",
            30, 0.5, 0.4, WHITE},
        {"Nobody win\0Ничья\0-\0-",
            30, 0.5, 0.4, WHITE},

        // Buttons texts
        {"Restart\0Перезапустить\0-\0-",
            24, 0.5, 0.5, WHITE},
        {"Exit to menu\0Выйти в меню\0-\0-",
            24, 0.5, 0.6, WHITE},
        {"Connect\0Присоединится\0-\0-",
            24, 0.5, 0.7, WHITE},
        {"Cancel\0Отмена\0-\0-",
            24, 0.5, 0.9, WHITE},

        // Server texts
        {"Wait for connection\0Ожидайте подключения\0-\0-",
            30, 0.5, 0.2, WHITE},
        {"Your port: %u\0Ваш порт: %u\0-%u\0-%u",
            30, 0.5, 0.4, WHITE},

        // Client texts
        {"Enter IP:\0Введите IP:\0-\0-",
            30, 0.5, 0.1, WHITE},
        {"Enter port:\0Введите порт:\0-\0-",
            30, 0.5, 0.4, WHITE},
    };

    // All framed texts buttons in game
    GUI::TextButton textButtons[BTN_count] = {
        // Select options
        {(GUI::TextButton)texts[TXT_SELECT_SINGLE]},
        {(GUI::TextButton)texts[TXT_SELECT_TWO]},
        {(GUI::TextButton)texts[TXT_SELECT_SERVER]},
        {(GUI::TextButton)texts[TXT_SELECT_CLIENT]},

        // Buttons texts
        {(GUI::TextButton)texts[TXT_BUTTON_RESTART]},
        {(GUI::TextButton)texts[TXT_BUTTON_MENU]},
        {(GUI::TextButton)texts[TXT_BUTTON_CONNECT]},
        {(GUI::TextButton)texts[TXT_BUTTON_CANCEL]},
    };

 public:
    Texts();   // Create and update all static texts
    void updateTranslation();  // Update translations of all texts
    void updateTitle();        // Update window title
};
