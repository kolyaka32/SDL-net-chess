/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../include.hpp"
#include "../dataTypes.hpp"


// Class of timer to control process sleep time
class IdleTimer {
 protected:
    const unsigned sleepTime;  // Time to next cycle
    timer lastSleep;           // Timer, when next cycle need to end
 public:
    explicit IdleTimer(unsigned sleepTime = 16);  // Time to sleep in miliseconds
    void sleep();                                 // Setting in idle state ("sleep")
};
