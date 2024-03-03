#pragma once

#include "baseGUI.hpp"
#include "values.hpp"

// Working with text
// Functions for setting text at his place and his text
void setAllText();  
// Function of updating translation of all texts
void updateTranslation(LNG_types language);
// Function of clearing text SELCTED_BOX_types
void clearAllText();

// Pause menu with settings
void pause();

// First loaded menu, where player can choose mode, choose settings
void selectMenu();

// Types of numerated static texts
enum TXT_types{
    // Selection menu 
    TXT_SELECT_ENTER,    // Game name
    TXT_SELECT_SINGLE,   // Singleplayer gamemode
    TXT_SELECT_TWO,      // Two player gamemode
    TXT_SELECT_SERVER,   // Host server
    TXT_SELECT_CLIENT,   // Connect to server

    // Pause texts
    TXT_PAUSE_PAUSE,     // Pause name
    TXT_PAUSE_MUSIC,     // Pause music slider text
    TXT_PAUSE_SOUND,     // Pause sound slider text

    // Game start texts
    TXT_START_SELECT,    // Text of selecting start shape

    // Stop menu
    TXT_STOP_WIN,        // Winning topic
    TXT_STOP_LOOSE,      // Loosing topic
    TXT_STOP_NOBODY,     // Topic of nobody win
    TXT_STOP_SKIP,       // Topping of skipping round
    TXT_STOP_WIN_1,      // First player win topic (for two players)
    TXT_STOP_WIN_2,      // Second player win topic (for two players)
    TXT_STOP_RESTART,    // Resatrt game button text
    TXT_STOP_MENU,       // Menu going button text

    // Internet texts
    TXT_INTERNET_TURN,   // Topic of turn of current player
    TXT_INTERNET_WAIT,   // Topic of waiting for turn

    // Server texts
    TXT_SERVER_WAIT,     // Server label of waiting to connect
    TXT_SERVER_PORT,     // Server label of current connect port

    // Client texts
    TXT_CLIENT_IP,       // IP enter label
    TXT_CLIENT_PORT,     // Port enter label
    TXT_CLIENT_CONNECT,  // Connect button text
    TXT_CLIENT_WAIT      // Start waiting label
};
// Summary text counter
#define TXT_count 25

// Declaring static text
extern GUI::staticText texts[TXT_count];

// Declaring global list of animations
#if ANI_count
extern Animation Advertisment[ANI_count];
#endif

extern GUI::Button esc;

// External values to save and load from settings file
extern LNG_types language;  // Language settings
extern Uint8 MusicVolume;  // Start volume of music
extern Uint8 EffectsVolume;  // Start volume of effects
extern Uint16 drawFPS;  // Setted frames per seconds
