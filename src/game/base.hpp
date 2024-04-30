#pragma once

#include "../GUI/baseGUI.hpp"
#include "../cycleTemplate.hpp"
#include "entity/board.hpp"


// Cycle with game template
class GameCycle : public virtual CycleTemplate
{
protected:
    Board board;  // Main game field
    Uint8 endState;  // State of game (end)

    // GUI objects
    // Button for quit settings menu
    //GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};
    // Ending options
    GUI::Backplate endBackplate{{70, 150, SCREEN_WIDTH - 140, SCREEN_HEIGHT - 300}, 40, 5};

    // New overrided cycle functions
    void getInput() override;     // Getting all user input (keyboard, mouse...)
    Uint8 mouseInput() override;  // Checking for any need mouse action
    void draw() const override;   // Drawing all needed objects
public:
    GameCycle();   // Start game cycle
    ~GameCycle();  // Close game cycle
};
