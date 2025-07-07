/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_Keyboard.h>
#include <SDL3/SDL_events.h>
#include "idleTimer.hpp"
#include "app.hpp"


// Template for any cycles
class CycleTemplate {
 private:
    static bool running;           // Flag of current running state
    IdleTimer idleTimer{1000/60};  // Timer to idle in main cycle

 protected:
    Mouse mouse;         // Position of mouse on screen

    // Cycle functions for cycle (should be overriden)
    void getInput(App& app);                  // Getting all user input
    virtual void update(App& app);            // Getting special objects update
    virtual void draw(const App& app) const;  // Draw all need objects

    // Subprograms for get need input
    virtual void inputMouseDown(App& app);                  // Actioning for mouse button pressing
    virtual void inputMouseUp(App& app);                    // Actioning for mouse button unpressing
    virtual void inputKeys(App& app, SDL_Keycode key);      // Actioning for any keys pressing
    virtual void inputMouseWheel(App& app, float _wheelY);  // Actioning for scrolling wheel
    virtual void inputText(App& app, const char* text);     // Actioning for typing text

 public:
    CycleTemplate();
    void run(App& app);
    // Function for stop current running cycle
    static void stop();
};
