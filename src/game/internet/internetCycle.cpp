/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


//
InternetCycle::InternetCycle() {
    // Launching process
    running = true;

    // Stopping from pre-launch
    gettingMutex.lock();
}

//
InternetCycle::~InternetCycle() {
    // Stopping all working proceses
    running = false;

    // Closing thread
    gettingCycle.join();
}

//
void InternetCycle::lauchCycle() {
    // Waiting for allowing to start
    gettingMutex.lock();
    gettingMutex.unlock();

    // Main getting cycle
    while (running) {
        // Waiting for posobility for get data
        gettingMutex.lock();

        // Getting data with check on exit
        if (update()) {
            running = false;
        }

        // Unlocking mutex for another actions
        gettingMutex.unlock();

        // Waiting next cycle (for better process time)
        internetTimer.sleep();
    }
}
