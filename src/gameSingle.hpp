
#pragma once

// Including other game fariations
#include "gameServer.hpp"
#include "gameClient.hpp"

// Game cycle, where one persone play with bote
void singleMainCycle();

// Game cycle, where two persons play against each other
void twoMainCycle();

// Global game variables
extern Uint8 gameState;           // State of game (from END_types)
extern bool waitTurn;             // Flag of waiting, until another user have his turn
extern bool runGame;              // Flag of running main game cycle
extern bool start;                // Flag of showing welcome screen with choosing command
extern Field field;               // Main game object
