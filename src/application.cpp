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
        case Cycle::Menu:
            // Cycle with game menu and selection of mode
            runCycle<SelectCycle>();
            break;

        case Cycle::Singleplayer:
            // Cycle with singplayer joke animation
            runCycle<SinglePlayerGameCycle>();
            break;

        case Cycle::LocalCOOP:
            // Cycle with game menu and selection of mode
            runCycle<TwoPlayerGameCycle>();
            break;

        case Cycle::ServerLobby:
            // Cycle with waiting in lobby for another player
            runCycle<ServerLobby>();
            break;

        case Cycle::ServerGame:
            // Game cycle with game part of server
            runCycle<ServerGame>();
            break;

        case Cycle::ClientLobby:
            // Cycle with trying to connect
            runCycle<ClientLobby>();
            break;

        case Cycle::ClientGame:
            // Game cycle with game part of client
            runCycle<ClientGame>();
            break;

        case Cycle::None:
        default:
        // Stopping current process
            running = false;
            break;
        }
    }
}

// Function for setting window title depend on language
void Window::updateTitle() const {
    // Setting window title
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        updateTitle("Chess on SDL");
        break;

    case Language::Russian:
        updateTitle("Шахматы на SDL");
        break;

    case Language::German:
        updateTitle("Schach на SDL");
        break;

    case Language::Bellarusian:
        updateTitle("Шахматы на SDL");
        break;
    }
}
