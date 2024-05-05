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
class Texts : public virtual App, public virtual InitFile
{
public:
    // All static texts in game
    GUI::StaticText texts[TXT_count] = {
        // Selection menu
        {"Chess\nШахматы\nSchach\nШахматы\n",
            30, 0.5, 0.1, WHITE},
        {"Singleplayer\nОдиночная игра\nEinzelspiel\nАдзіночная гульня\n",
            24, 0.5, 0.3, WHITE},
        {"Two players\nДва игрока\nZwei Spieler\nДва гульца\n",
            24, 0.5, 0.5, WHITE},
        {"Create server\nСоздать сервер\nServer erstellen\nСтварыць сервер\n",
            24, 0.5, 0.7, WHITE},
        {"Connect\nПрисоединиться\nBeitreten\nДалучыцца\n",
            24, 0.5, 0.9, WHITE},
        
        // Pause menu
        {"Pause\nПауза\nPause\nПаўза\n", 
            30, 0.5, 0.1},
        {"Music\nМузыка\nDie Musik\nМузыка\n", 
            30, 0.5, 0.68},
        {"Sounds\nЗвуки\nGeräusche\nГук\n", 
            30, 0.5, 0.83},

        // Game turnes
        {"First player turn\nХод первого игрока\n-\n",
            24, 0.5, 0.1, WHITE},
        {"Second player turn\nХод второго игрока\n-\n",
            24, 0.5, 0.1, WHITE},
        {"Your turn\nВаш ход\n-\n",
            24, 0.5, 0.1, WHITE},
        {"Wait\nОжидайте\n-\n",
            24, 0.5, 0.1, WHITE},

        // Game end texts
        {"Win!\nПобеда!\n-\n",
            30, 0.5, 0.4, WHITE},
        {"Fist player win!\nПервый игрок выйграл!\n-\n",
            30, 0.5, 0.4, WHITE},
        {"Second player win!\nВторой игрок выйграл!\n-\n",
            30, 0.5, 0.4, WHITE},
        {"You loose...\nВы проиграли...\n-\n-\n",
            30, 0.5, 0.4, WHITE},
        {"Nobody win\nНичья\n-\n-\n",
            30, 0.5, 0.4, WHITE},

        // Buttons texts
        {"Restart\nПерезапустить\n-\n-\n",
            24, 0.5, 0.5, WHITE},
        {"Exit to menu\nВыйти в меню\n-\n-\n",
            24, 0.5, 0.6, WHITE},
        {"Connect\nПрисоединится\n-\n-\n",
            24, 0.5, 0.7, WHITE},
        {"Cancel\nОтмена\n-\n-\n",
            24, 0.5, 0.9, WHITE},

        // Server texts
        {"Wait for connection\nОжидайте подключения\n-\n-\n",
            30, 0.5, 0.2, WHITE},
        {"Your port: %\nВаш порт: %\n-\n-\n",
            30, 0.5, 0.4, WHITE},

        // Client texts
        {"Enter IP:\nВведите IP:\n-\n-\n",
            30, 0.5, 0.1, WHITE},
        {"Enter port:\nВведите порт:\n-\n-\n",
            30, 0.5, 0.4, WHITE},
    };
    
    // All framed texts buttons in game
    GUI::TextButton textButtons[BTN_count] = {
        // Select options
        {texts[TXT_SELECT_SINGLE]},
        {texts[TXT_SELECT_TWO]},
        {texts[TXT_SELECT_SERVER]},
        {texts[TXT_SELECT_CLIENT]},

        // Buttons texts
        {texts[TXT_BUTTON_RESTART]},
        {texts[TXT_BUTTON_MENU]},
        {texts[TXT_BUTTON_CONNECT]},
        {texts[TXT_BUTTON_CANCEL]},
    };

public:
    Texts();   // Create and update all static texts
    void updateTranslation();  // Update translations of all texts
};
