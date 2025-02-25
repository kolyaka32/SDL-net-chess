/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"

// Cycles
#include "../cycles/selectCycle.hpp"
#include "../cycles/singlePlayer.hpp"
#include "../cycles/twoPlayer.hpp"

App::App()
: window{loader},
music{loader},
sounds{loader} {}

App::~App() {}

void App::stop() {
    running = false;
}

void App::startNextCycle(CYCLE_types _type) {
    nextCycle = _type;
}

void App::run() {
    // Running application
    while (running) {
        // Switching between running options
        switch (nextCycle) {
        case CYCLE_MENU:
            {
                // Cycle with game menu and selection of mode
                SelectCycle cycle(window);
                cycle.run(*this);
            }
            break;
        
        case CYCLE_SINGLEPLAYER:
            {
                // Cycle with singplayer joke animation
                SinglePlayerGameCycle cycle(*this);
                cycle.run(*this);
            }
            break;

        case CYCLE_LOCALCOOP:
            {
                // Cycle with game menu and selection of mode
                TwoPlayerGameCycle cycle(window);
                cycle.run(*this);
            }
            break;

        // Stopping current process
        case CYCLE_NONE:
        default:
            running = false;
            break;
        }
    }
    
}
