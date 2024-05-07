#include "idleTimer.hpp"

//
IdleTimer::IdleTimer(int _sleepTime) : sleepTime(_sleepTime){
    // Resetting timer
    lastSleep = SDL_GetTicks64() + sleepTime;
};

//
void IdleTimer::sleep(){
    timer cutTime = SDL_GetTicks64();

    // Check, if idle need
    if(SDL_GetTicks64() < lastSleep){
        // Sleep rest time
        SDL_Delay(lastSleep - SDL_GetTicks64());

        // Updating timer for next sleep
        lastSleep = SDL_GetTicks64() + sleepTime;
    }
};
