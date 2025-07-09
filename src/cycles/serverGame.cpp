/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGame::ServerGame(App& _app, Connection& _server)
: GameCycle(_app),
connection(_server) {
    if(!App::isRestarted()) {
        // Sending applying initialsiation message
        connection.sendConfirmed(ConnectionCode::Init);

        // Starting main song (if wasn't started)
        _app.music.start(MUS_MAIN);
    }
}

void ServerGame::inputMouseDown(App& _app) {
    // Clicking in settings menu
    if (settings.click(mouse)) {
        return;
    }
    // Exiting to menu
    if (exitButton.in(mouse)) {
        stop();
        return;
    }
}

void ServerGame::update(App& _app) {
    BaseCycle::update(_app);

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        
        return;
    }
}

void ServerGame::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Drawing buttons
    exitButton.blit(_app.window);

    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
