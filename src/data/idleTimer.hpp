/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "time.hpp"


// Class of timer to control process sleep time
class IdleTimer {
protected:
    const unsigned sleepTime;  // Time to next cycle
    timer lastSleep;           // Timer, when next cycle need to end
public:
    IdleTimer(unsigned sleepTime = 1000/60);  // Time to sleep in miliseconds
    void sleep();                             // Setting in idle state ("sleep")
};
