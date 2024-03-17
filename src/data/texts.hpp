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
};

// Summary text counter
#define TXT_count 8


// All static texts
class Texts : public virtual App, public virtual InitFile
{
public:
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
    };

public:
    Texts();   // Create and update all static texts
    void updateTranslation();  // Update translations of all texts
};
