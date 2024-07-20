/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "data.hpp"
#include "idleTimer.hpp"

// Template for any cycles
class CycleTemplate {
 protected:
    IdleTimer idleTimer{1000/data.drawFPS};  // Timer to idle in main cycle

    // Data for cycle
    bool running = true;    // Flag of running current cycle
    int mouseX, mouseY;     // Current position of mouse

    // Run internal cycle
    template <class Cycle>
    bool runCycle();

    // Run internal cycle with parameters
    template <class Cycle, typename Param>
    bool runCycle(Param args);

    // Cycle functions for cycle (should be overriden)
    void getInput();            // Getting all user input
    virtual void draw() const;  // Draw all need objects
    virtual void update();      // Getting special objects update (if need)

    // Subproframs for get need input
    virtual bool getMouseInput();                          // Checking for any mouse actions
    virtual bool getKeysInput(const SDL_Keysym& key);      // Checking for any keys actions
    virtual bool getAnotherInput(const SDL_Event& event);  // Getting all rest user input

 public:
    explicit CycleTemplate();
    virtual void run();
};


// Realisations
// Run internal cycle
template <class Cycle>
bool CycleTemplate::runCycle() {
    // Entering cycle for correct updations
    data.updateList.enterCycle();

    // Launching new cycle
    Cycle cycle;

    // Running cycle
    cycle.run();

    // Checking for exit
    if (!data.appRunning) {
        return true;
    }

    // Exiting updation cycle
    data.updateList.exitCycle();

    // Normal return
    return false;
}

// Run cycle with parameters
template <class Cycle, typename Param>
bool CycleTemplate::runCycle(Param args) {
    // Entering cycle for correct updations
    data.updateList.enterCycle();

    // Launching new cycle
    Cycle cycle(args);

    // Running cycle
    cycle.run();

    // Checking for exit
    if (!data.appRunning) {
        return true;
    }

    // Exiting updation cycle
    data.updateList.exitCycle();

    // Normal return
    return false;
}