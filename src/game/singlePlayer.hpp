#pragma once

#include "../cycleTemplate.hpp"


//
class SinglePlayerGameCycle : public CycleTemplate
{
private:
    // Data for transition to animation
    Uint16 currentWidth = 8;
    Uint16 currentHeight = 8;

    // Data for board animation
    const ANI_names type = ANI_SINGLEPLAYER;
    const Uint16 width, height;   // Parameters of image
    Uint16 frame;                 // Current frame of animation
    timer prevFrameUpdate;        // Timer, when was last frame change

    // Main run functions
    //void getInput();     // Getting all user input
    void draw() const override;  // Draw all need objects
    void update() override;      // Getting special objects update (if need)

    // Get input subprograms
    //virtual bool getMouseInput();  // Checking for any mouse actions
    //virtual bool getKeysInput(SDL_Keysym& key);   // Checking for any keys actions
    //virtual bool getAnotherInput(SDL_Event& event);  // Getting all other user input

public:
    SinglePlayerGameCycle();
    ~SinglePlayerGameCycle();
};
