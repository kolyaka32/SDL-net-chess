/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"

// Cycles
#include "cycles/selectCycle.hpp"
#include "cycles/singlePlayer.hpp"
#include "cycles/twoPlayer.hpp"
#include "cycles/serverLobby.hpp"
#include "cycles/serverGame.hpp"
#include "cycles/clientLobby.hpp"
#include "cycles/clientGame.hpp"


// Function with selecting starting cycle
void App::run() {
    // Running application
    while (running) {
        // Switching between running options
        switch (nextCycle) {
        case CYCLE_MENU:
            {
                // Cycle with game menu and selection of mode
                SelectCycle cycle(*this);
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
                TwoPlayerGameCycle cycle(*this);
                cycle.run(*this);
            }
            break;

        case CYCLE_SERVER_LOBBY:
            {
                // Cycle with waiting in lobby for another player
                ServerLobby cycle(*this);
                cycle.run(*this);
            }
            break;

        case CYCLE_SERVER_GAME:
            {
                // Game cycle with game part of server
                ServerGame cycle(*this);
                cycle.run(*this);
            }
            break;

        case CYCLE_CLIENT_LOBBY:
            {
                // Cycle with trying to connect
                ClientLobby cycle(*this);
                cycle.run(*this);
            }
            break;

        case CYCLE_CLIENT_GAME:
            {
                // Game cycle with game part of client
                ClientGame cycle(*this);
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

// Function for setting window title depend on language
void Window::updateTitle() const {
    // Setting window title
    switch (currentLanguage) {
    case LNG_ENGLISH:
        updateTitle("Chess on SDL");
        break;

    case LNG_RUSSIAN:
        updateTitle("Шахматы на SDL");
        break;

    case LNG_GERMAN:
        updateTitle("Schach на SDL");
        break;

    case LNG_BELARUSIAN:
        updateTitle("Шахматы на SDL");
        break;
    }
}
