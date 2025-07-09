/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "selectCycle.hpp"


ClientGame::ClientGame(App& _app, Connection& _client)
: BaseCycle(_app),
connection(_client) {
    // Starting main song (if wasn't started)
    if(!_app.isRestarted()) {
        _app.music.start(MUS_MAIN);
    }
}

void ClientGame::inputMouseDown(App& _app) {
    // Clicking in settings menu
    if (settings.click(mouse)) {
        return;
    }
    // Checking on exit
    if (exitButton.in(mouse)) {
        // Returning to menu
        stop();
        return;
    }
}

void ClientGame::update(App& _app) {
    BaseCycle::update(_app);

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        
        return;

    case ConnectionCode::GameRestart:
        
        return;
    }
}

void ClientGame::draw(const App& _app) const {
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
