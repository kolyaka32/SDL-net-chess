#pragma once

#include <thread>
#include <mutex>
#include "data/data.hpp"


// Template for any cycles
class CycleTemplate
{
private:
    void drawCycle();  // Process to run in side thread
    std::thread drawThread{this->drawCycle, this};  // Thread for drawing
protected:
    // Data for own cycle
    bool running = true;    // Flag of running current cycle (for control draw)
    std::mutex runMutex;    // Mutex for block running for change for another
    int mouseX, mouseY;     // Current position of mouse
    Uint8 selectedBox;      // Number of which box is currently selected
    const MUS_names music;  // Music track to play

    // Function for run internal cycle
    template <typename Cycle>
    Uint8 runCycle();

    // Cycle functions for own cycle (must be overriden)
    virtual void getInput();     // Getting all user input (keyboard, mouse...)
    virtual Uint8 mouseInput();  // Checking for any need mouse action
    virtual void draw() const;   // Draw all need objects
public:
    CycleTemplate(MUS_names music = MUS_START_NONE);
    ~CycleTemplate();
    void run();  // Start cycle
};


// Realisation of running internal cycle
template <typename Cycle>
Uint8 CycleTemplate::runCycle(){
    // Stopping all current threads
    runMutex.lock();

    // Launching new cycle
    Cycle cycle;
    cycle.run();

    // Unlocking all threads
    runMutex.unlock();

    // Continuing playing music track
    if(cycle.music){
        data.playMusic(music);
    }

    // Checking for exit
    if(!data.running){
        return 1;
    }

    // Normal return
    return 0;
};
