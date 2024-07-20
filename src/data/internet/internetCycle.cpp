/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


// Internet cycle class
InternetCycle::InternetCycle() {}

// Own function for start need cycle
void InternetCycle::run() {
    // Starting main cycle
    while (running) {
        // Getting user input
        getInput();

        // Updating internet module
        updateInternet();

        // Updating other stuff
        update();

        // Drawing interface
        draw();

        // Standing in idle state
        idleTimer.sleep();
    }
}

// Updating internet connection
void InternetCycle::updateInternet() {
    // Check, if too much time since last message send
    checkSendTimeout();

    // Checking, if messages wasn't delivered
    checkNeedResend();

    // Check, if get new message
    if (checkGetMessage()) {
        // Stopping cycle
        running = false;
        return;
    }

    // Check, if lost connection from other side
    if (checkDisconect()) {
        // Stopping cycle
        running = false;
        return;
    }
}
