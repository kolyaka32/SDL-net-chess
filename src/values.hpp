// Base in-game global structs
#pragma once

#include "include.hpp"
#include <string>
#include "dataTypes.hpp"

// Flags of running
extern bool running;  // Flag of main cycle work
extern bool restart;  // Flag of restarting whole game with other parameters

// External values to save and load from settings file
extern Uint8 language;  // Language settings
extern Uint8 MusicVolume;  // Start volume of music
extern Uint8 EffectsVolume;  // Start volume of effects
extern Uint16 drawFPS;  // Setted frames per seconds


// Game parameters (for game and multiplayer part)
/*extern Uint8 fieldWidth;      // Width and height of field
extern Uint8 winWidth;        // Width, which need for win
extern Uint8 queue;           // Queue of current player
extern Uint8 player;          // Number of player, which selected
extern std::string baseIP;    // Saved ip for better expirience
extern std::string basePort;  // Saved connection port for better expirience*/
