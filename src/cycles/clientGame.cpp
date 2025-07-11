/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "selectCycle.hpp"


bool ClientGame::currentTurn = false;

ClientGame::ClientGame(App& _app, Connection& _client)
: GameCycle(_app),
connection(_client) {
    if(!App::isRestarted()) {
        // Resetting game
        endState = END_NONE;
        currentTurn = false;
        board.reset();
    }
}

void ClientGame::inputMouseDown(App& _app) {
    if (settings.click(mouse)) {
        return;
    }
    if (exitButton.in(mouse)) {
        stop();
        return;
    }
    // Checking, if game start
    if (endState <= END_TURN) {
        // Check, if turn of current player
        if (currentTurn) {
            // Clicking on field
            endState = board.click(_app.sounds, mouse);

            // Check, if change state
            if (endState != END_NONE) {
                currentTurn = false;
                // Sending turn to opponent
                connection.sendConfirmed(ConnectionCode::GameTurn, board.getLastTurnStart(), board.getLastTurnEnd());
            }
        }
        return;
    }
    // Waiting menu
    if (menuButton.in(mouse)) {
        // Going to menu
        stop();
        return;
    }
}

void ClientGame::inputKeys(App& _app, const SDL_Keycode _key) {
    // If not restart - act like normal key input
    if (_key != SDLK_R) {
        GameCycle::inputKeys(_app, _key);
    }
}

void ClientGame::update(App& _app) {
    BaseCycle::update(_app);

    // Getting internet messages
    switch (connection.updateMessages()) {
    case ConnectionCode::GameTurn:
        // Check, if turn of another player (for security)
        if (currentTurn == false) {
            #if CHECK_CORRECTION
            SDL_Log("Turn of opponent player: from %u to %u", connection.lastPacket->getData<Uint8>(2), connection.lastPacket->getData<Uint8>(3));
            #endif
            endState = board.move(_app.sounds, {connection.lastPacket->getData<Uint8>(2)}, {connection.lastPacket->getData<Uint8>(3)});
            currentTurn = true;
        }
        return;

    case ConnectionCode::GameRestart:
        #if CHECK_CORRECTION
        SDL_Log("Game restart by server");
        #endif
        // Resetting game
        endState = END_NONE;
        currentTurn = false;
        board.reset();
        // Making sound
        _app.sounds.play(SND_RESET);
        return;
    }
}

void ClientGame::draw(const App& _app) const {
    // Bliting field
    board.blit(_app.window);

    // Draw surround letters
    letters.blit(_app.window);

    // Drawing player state (inversed)
    playersTurnsTexts[3 - currentTurn].blit(_app.window);

    // Drawing buttons
    exitButton.blit(_app.window);

    // Bliting game state, if need
    if (endState > END_TURN) {
        // Bliting end background
        endBackplate.blit(_app.window);

        // Bliting text with end state
        switch (endState) {
        case END_WIN:
            looseText.blit(_app.window);
            break;

        case END_LOOSE:
            winText.blit(_app.window);
            break;

        case END_NOBODY:
            nobodyWinText.blit(_app.window);
            break;
        }

        // Blitting buttons
        menuButton.blit(_app.window);
    }
    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
