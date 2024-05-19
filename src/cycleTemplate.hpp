/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <thread>
#include <mutex>

#include "data/data.hpp"
#include "data/idleTimer.hpp"

// Template for any cycles
class CycleTemplate {
 private:
    // Private data for draw
    void drawCycle();  // Process to draw graphics, run sidely by another thread
    std::thread drawThread{this->drawCycle, this};  // Thread for drawing
    IdleTimer drawTimer{1000/data.drawFPS};   // Timer to idle in draw cycle

 protected:
    // Data for cycle
    bool running = true;    // Flag of running current cycle
    std::mutex runMutex;    // Mutex for block running of current cycle
    IdleTimer inputTimer{1000/INPUT_FPS};  // Timer to idle in input cycle
    int mouseX, mouseY;     // Current position of mouse
    Uint8 selectedBox;      // Number of which box is currently selected
    const MUS_names music;  // Music track to play (or NULL, if not need start)

    // Function for run internal cycle
    template <typename Cycle>
    Uint8 runCycle();

    // Cycle functions for cycle (must be overriden)
    virtual void getInput();     // Getting all user input (keyboard, mouse...)
    virtual Uint8 mouseInput();  // Checking for any need mouse action
    virtual void draw() const;   // Draw all need objects

 public:
    explicit CycleTemplate(MUS_names music = MUS_START_NONE);
    void run();  // Start cycle
};


// Realisation of running internal cycle
template <typename Cycle>
Uint8 CycleTemplate::runCycle() {
    // Stopping all current threads
    runMutex.lock();

    // Launching new cycle
    Cycle cycle;
    cycle.run();

    // Unlocking all threads
    runMutex.unlock();

    // Continuing playing music track
    if (cycle.music) {
        data.playMusic(music);
    }

    // Checking for exit
    if (!data.running) {
        return 1;
    }

    // Normal return
    return 0;
}
