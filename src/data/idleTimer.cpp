/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "idleTimer.hpp"


// Creating timer with first resetting timer
IdleTimer::IdleTimer(unsigned _sleepTime)
: sleepTime(_sleepTime) {
    // Resetting timer
    lastSleep = getTime() + sleepTime;
}

// Check, if need sleep and sleep it
void IdleTimer::sleep() {
    // Check, if idle need
    if (getTime() < lastSleep) {
        // Sleep rest time
        SDL_Delay(lastSleep - getTime());
    }
    // Updating timer for next sleep
    lastSleep = getTime() + sleepTime;
}
