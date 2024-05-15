#include "idleTimer.hpp"


// Creating timer with first resetting timer
IdleTimer::IdleTimer(int _sleepTime)
: sleepTime(_sleepTime) {
    // Resetting timer
    lastSleep = SDL_GetTicks64() + sleepTime;
}

// Check, if need sleep and sleep it
void IdleTimer::sleep() {
    // Check, if idle need
    if (SDL_GetTicks64() < lastSleep) {
        // Sleep rest time
        SDL_Delay(lastSleep - SDL_GetTicks64());

        // Updating timer for next sleep
        lastSleep = SDL_GetTicks64() + sleepTime;
    }
}
