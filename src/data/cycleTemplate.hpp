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
    virtual void inputMouseDown(App& app);                  // Actioning for mouse button pressing
    virtual void inputMouseUp(App& app);                    // Actioning for mouse button unpressing
    virtual void inputKeys(App& app, SDL_Keycode key);      // Actioning for any keys pressing
    virtual void inputMouseWheel(App& app, float _wheelY);  // Actioning for scrolling wheel
    virtual void inputText(App& app, const char* text);     // Actioning for typing text

public:
    CycleTemplate();
    void run(App& app);
};
