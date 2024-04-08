#pragma once

#include "../cycleTemplate.hpp"
#include "entity/board.hpp"

// Global game variables
/*extern Uint8 gameState;           // State of game (from END_types)
extern bool waitTurn;             // Flag of waiting, until another user have his turn
extern bool runGame;              // Flag of running main game cycle
extern bool start;                // Flag of showing welcome screen with choosing command
extern Field field;               // Main game object
*/


// Cycle with game template
class GameCycle : public CycleTemplate
{
protected:
    Board board;  // Main game field

    // GUI objects
    // Button for quit settings menu
    //GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    void getInput() override;     // Getting all user input (keyboard, mouse...)
    Uint8 mouseInput() override;  // Checking for any need mouse action
    void draw() const override;   // Drawing all needed objects
public:
    GameCycle();   // Start game cycle
    ~GameCycle();  // Close game cycle
};
