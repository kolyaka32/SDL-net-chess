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
    static bool restarting;        // Flag, if game was restarted
    static bool additionalRestart; // Flag of additional game restart
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
    static void restart();
    static bool isRestarted();
    static bool isAdditionalRestarted();
    // Function for starting new cycle with posible arguments
    template <class T, typename ...Args>
    static void runCycle(App& app, const Args& ...args);
};


template <class T, typename ...Args>
void CycleTemplate::runCycle(App& _app, const Args& ...args) {
    restarting = false;
    additionalRestart = false;

    // Running current cycle, while restarting
    do {
        // Updating title location
        _app.window.updateTitle();
        // Launching new cycle
        T cycle(_app, args...);
        cycle.run(_app);
    } while (_app.isRunning() && (restarting | additionalRestart));

    // Restarting external running cycle for correct language change
    additionalRestart = true;
    running = false;
}
