#pragma once

#include "../include.hpp"
#include "../dataTypes.hpp"


// Class of timer to control process sleep time
class IdleTimer
{
protected:
    const unsigned sleepTime;  // Time to next cycle
    timer lastSleep;           // Timer, when next cycle need to end
public:
    IdleTimer(int sleepTime = 1000/60);  // Time to sleep in miliseconds
    void sleep();                        // Setting in idle state ("sleep")
};