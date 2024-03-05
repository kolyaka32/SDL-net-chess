#pragma once

#include "GUI/baseGUI.hpp"

// Types of numerated static texts
enum TXT_types{
    // Selection menu 
    TXT_SELECT_ENTER,    // Game name
    TXT_SELECT_SINGLE,   // Singleplayer gamemode
    TXT_SELECT_TWO,      // Two player gamemode
    TXT_SELECT_SERVER,   // Host server
    TXT_SELECT_CLIENT    // Connect to server
};

// Summary text counter
#define TXT_count 5

// Types of language
enum LNG_types{
    LNG_ENGLISH,    // English language
    LNG_RUSSIAN,    // Russian language
    LNG_GERMAN,     // German language
    LNG_BELARUSIAN  // Belarusian language
};

#define LNG_count 4  // Final counter of all languages


// All static texts
class Texts : public App
{
public:
    GUI::staticText texts[TXT_count] = {
        // Selection menu
        {"Tic-tac-toe\nКрестики нолики\n", 
            24, 0.5, 0.1},
        {"Singleplayer\nОдиночная игра\n", 
            24, 0.5, 0.3},
        {"Two players\nДва игрока\n", 
            24, 0.5, 0.5},
        {"Create server\nСоздать сервер\n", 
            24, 0.5, 0.7},
        {"Connect\nПрисоединится\n", 
            24, 0.5, 0.9},
    };

public:
    Texts();
    ~Texts();
    void updateTranslation();
};
