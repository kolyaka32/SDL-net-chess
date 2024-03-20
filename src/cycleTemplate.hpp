#pragma once

#include <thread>
#include <mutex>
#include "data/data.hpp"


//
class CycleTemplate
{
private:
    void drawCycle();  // Process to run in side thread
    std::thread drawThread{this->drawCycle, this};  // Thread for drawing
protected:
    // Data for own cycle
    //bool LMBclick;  // Flag of current mouse clicking state
    //bool stop = false;  // Flag of stopping current process
    std::mutex runMutex;  // Mutex for block running for change for another
    int mouseX, mouseY;   // Current position of mouse
    Uint8 selectedBox;    // Number of which box is currently selected

    // Cycle functions for own cycle (must be overriden)
    virtual void getInput();     // Getting all user input (keyboard, mouse...)
    virtual Uint8 mouseInput();  // Checking for any need mouse action
    virtual void draw();         // Draw all need objects
public:
    CycleTemplate();
    ~CycleTemplate();
    void run();         // Start cycle
};
