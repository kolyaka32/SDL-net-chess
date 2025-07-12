/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


bool ServerGame::currentTurn = false;

ServerGame::ServerGame(App& _app, Connection& _server)
: GameCycle(_app),
connection(_server) {
    if(!App::isRestarted()) {
        // Sending applying initialsiation message
        connection.sendConfirmed(ConnectionCode::Init);
        // Resetting game
        endState = END_NONE;
        currentTurn = true;
        board.reset();
    }
}

void ServerGame::inputMouseDown(App& _app) {
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
    if (restartButton.in(mouse)) {
        #if CHECK_CORRECTION
        SDL_Log("Game restart by current user");
        #endif
        // Restarting current game
        endState = END_NONE;
        currentTurn = true;
        // Resetting field
        board.reset();
        // Making sound
        _app.sounds.play(SND_RESET);
        return;
    }
    if (menuButton.in(mouse)) {
        // Going to menu
        stop();
        return;
    }
}

void ServerGame::inputKeys(App& _app, SDL_Keycode _key) {
    if (_key == SDLK_R) {
        // Sending message of game restart
        connection.sendConfirmed(ConnectionCode::GameRestart);
        // Restarting current game
        endState = END_NONE;
        currentTurn = true;
        // Resetting field
        board.reset();
        // Making sound
        _app.sounds.play(SND_RESET);
        return;
    } else {
        GameCycle::inputKeys(_app, _key);
    }
}

void ServerGame::update(App& _app) {
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
    }
}

void ServerGame::draw(const App& _app) const {
    // Bliting field
    board.blit(_app.window);

    // Draw surround letters
    letters.blit(_app.window);

    // Drawing player state
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
            winText.blit(_app.window);
            break;

        case END_LOOSE:
            looseText.blit(_app.window);
            break;

        case END_NOBODY:
            nobodyWinText.blit(_app.window);
            break;
        }

        // Blitting buttons
        restartButton.blit(_app.window);
        menuButton.blit(_app.window);
    }
    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
