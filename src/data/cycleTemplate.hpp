/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_Keyboard.h>
#include <SDL3/SDL_events.h>
#include "idleTimer.hpp"
#include "app.hpp"
#include "../GUI/baseGUI.hpp"


// Template for any cycles
class CycleTemplate {
private:
    bool running = true;           // Flag of current running state
    static bool restarted;         // Flag of cycle was restarted (by changing language)
    IdleTimer idleTimer{1000/60};  // Timer to idle in main cycle

protected:
    // Data for cycle
    float mouseX, mouseY;   // Current position of mouse
    void updateMousePos();  // Update mouseX and mouseY
    void stop();            // Stopping current cycle
    void restart();         // Set that cycle to restart with rememering it
    bool isRestarted();     // Tell, if cycle was restarted

    // Cycle functions for cycle (should be overriden)
    void getInput(App& app);                  // Getting all user input
    virtual void update(App& app);            // Getting special objects update
    virtual void draw(const App& app) const;  // Draw all need objects

    // Subproframs for get need input
    virtual void getMouseInput(App& app);                            // Checking for any mouse actions
    virtual void getKeysInput(App& app, SDL_Keycode key);            // Checking for any keys actions
    virtual void getAnotherInput(App& app, const SDL_Event& event);  // Getting all rest user input

public:
    CycleTemplate();
    void run(App& app);
};
