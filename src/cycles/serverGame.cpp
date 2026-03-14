/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serverGame.hpp"


ServerGameCycle::ServerGameCycle(Window& _window)
: InternetCycle(_window),
menu(_window) {
    if(!isRestarted()) {
        menu.reset();
        // Resetting game
        //endState = END_NONE;
        currentTurn = true;
        board.reset();
        // Sending first field
        internet.sendAllConfirmed({ConnectionCode::GameNew, field.getSave()});
    }
    logAdditional("Start server game cycle");
}

ServerGameCycle::~ServerGameCycle() {
    // Check, if not launching game
    if (!isRestarted()) {
        // Sending message of disconect
        internet.disconnect();
        // Clear getting socket
        internet.close();
    }
}

bool ServerGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    /*
    if (gameRestartButton.in(mouse)) {
        #if CHECK_CORRECTION
        SDL_Log("Game restart by current user");
        #endif
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
    }
    */
    if (gameSaveButton.in(mouse)) {
        // Save current game field
        menu.addField(field.saveField());
        // Showing message of sucsessful saving
        savedInfo.reset();
        logAdditional("Saving field");
    }
    if (gameMenuButton.in(mouse)) {
        // Starting game menu
        menu.activate();
        return true;
    }
    // Checking, if game start
    if (menu.isActive()) {
        if (const Field* f = menu.click(mouse)) {
            // Setting new field localy
            board.setNewField(f, window);
            // Sending it
            internet.sendAllConfirmed({ConnectionCode::GameNew, field.getSave()});
            menu.reset();
            logAdditional("Selecting new field");
        }
        return true;
    } else {
        // Normal turn
        if (field.tryClickServerCurrent(mouse)) {
            // Sending to opponent
            internet.sendAllConfirmed({ConnectionCode::GameTurn, field.getLastTurn(mouse)});
        }
        /*
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
        }*/
    }
    return false;
}

void ServerGameCycle::inputMouseUp() {
    InternetCycle::inputMouseUp();
    menu.unclick();
}

void ServerGameCycle::inputKeys(SDL_Keycode _key) {
    if (_key == SDLK_ESCAPE) {
        // Closing top open object
        if (menu.isActive()) {
            menu.escape();
        } else {
            settings.activate();
        }
        return;
    }
    InternetCycle::inputKeys(_key);
}

void ServerGameCycle::inputMouseWheel(float _wheelY) {
    if (settings.scroll(mouse, _wheelY)) {
        return;
    }
    menu.scroll(_wheelY);
}

void ServerGameCycle::getInternetPacket(const GetPacket& packet) {
    // Getting internet messages
    switch (ConnectionCode(packet.getData<Uint8>(0))) {
    case ConnectionCode::Quit:
        termianatedBox.activate();
        break;

    case ConnectionCode::GameTurn:
        if (packet.isBytesAvaliable(3)) {
            // Check, if turn of another player (for security)
            if (currentTurn == false) {
                logAdditional("Turn of opponent player: from %u to %u",
                    packet.getData<Uint8>(2), packet.getData<Uint8>(3));
                endState = board.move({packet.getData<Uint8>(2)}, {packet.getData<Uint8>(3)});
                currentTurn = true;
            }
        }
        break;

    default:
        break;
    }
}

void ServerGameCycle::update() {
    InternetCycle::update();
    menu.update();
}

void ServerGameCycle::draw() const {
    // Blitting field
    board.blit();

    // Draw game state
    switch (field.getState()) {
    case GameState::CurrentPlay:
        playersTurnsTexts[0].blit();
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[1].blit();
        break;

    case GameState::CurrentWin:
        winText.blit();
        break;

    case GameState::OpponentWin:
        looseText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
        break;

    default:
        break;
    }

    // Bliting waiting menu, if need
    menu.blit();

    // Drawing buttons
    exitButton.blit();
    gameSaveButton.blit();
    gameMenuButton.blit();
    settings.blit();

    // Messages
    savedInfo.blit();
    disconnectedBox.blit();
    termianatedBox.blit();

    // Bliting all to screen
    window.render();
}
