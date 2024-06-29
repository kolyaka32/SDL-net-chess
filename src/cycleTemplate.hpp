/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data/data.hpp"
#include "data/idleTimer.hpp"

// Template for any cycles
class CycleTemplate {
 protected:
    IdleTimer idleTimer{1000/data.drawFPS};  // Timer to idle in main cycle

    // Data for cycle
    bool running = true;    // Flag of running current cycle

    int mouseX, mouseY;     // Current position of mouse
    Uint8 selectedBox;      // Number of which box is currently selected
    const MUS_names music;  // Music track to play (or NULL, if not need start)

    // Function for run internal cycle
    template <class Cycle>
    bool runCycle();

    // Cycle functions for cycle (should be overriden)
    // Main run functions
    void getInput();            // Getting all user input
    virtual void draw() const;  // Draw all need objects
    virtual void update();      // Getting special objects update (if need)

    // Get input subprograms
    virtual bool getMouseInput();                          // Checking for any mouse actions
    virtual bool getKeysInput(const SDL_Keysym& key);      // Checking for any keys actions
    virtual bool getAnotherInput(const SDL_Event& event);  // Getting all other user input

 public:
    explicit CycleTemplate(MUS_names music = MUS_START_NONE);
    virtual void run();  // Main run cycle
};


// Realisation of running internal cycle
template <class Cycle>
bool CycleTemplate::runCycle() {
    // Entering cycle for correct updations
    data.updateList.enterCycle();

    // Launching new cycle
    Cycle cycle;

    // Running cycle
    cycle.run();

    // Continuing playing music track
    if (cycle.music) {
        data.playMusic(music);
    }

    // Checking for exit
    if (!data.appRunning) {
        return true;
    }

    // Exiting updation cycle
    data.updateList.exitCycle();

    // Normal return
    return false;
}
