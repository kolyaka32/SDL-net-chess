/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "clientGame.hpp"
#include "../game/selectingMenu/savedFields.hpp"


ClientGameCycle::ClientGameCycle(Window& _window)
: InternetCycle(_window),
waitText(window, 0.5, 0.05, {"Wait start", "Ожидайте начала", "Warte auf Start", "Чаканне старту"}) {
    logAdditional("Start client game cycle");
}

ClientGameCycle::~ClientGameCycle() {
    // Check, if not launching game
    if (!isRestarted()) {
        // Sending message of disconect
        internet.disconnect();
        // Clear getting socket
        internet.close();
    }
}

void ClientGameCycle::getInternetPacket(const GetPacket& packet) {
    // Getting internet messages
    switch (ConnectionCode(packet.getData<Uint8>(0))) {
    case ConnectionCode::Quit:
        termianatedBox.activate();
        return;

    case ConnectionCode::GameTurn:
        if (packet.isBytesAvaliable(3)) {
            board.clickClientOpponent(packet.getData<Uint8>(2), packet.getData<Uint8>(3));
            logAdditional("Turn of opponent player from %u to %u",
                packet.getData<Uint8>(2), packet.getData<Uint8>(3));
        }
        return;

    case ConnectionCode::GameNew:
        if (packet.isBytesAvaliable(69)) {
            // Creating new field from get data
            const FieldSave fieldSave{(char*)(packet.getPointer(2))};
            // Setting it as current
            board = (Field)fieldSave;

            // Making sound
            audio.sounds.play(Sounds::Reset);
            audio.music.startFromCurrent(Music::Main);
            logAdditional("Starting new game by connection");
        }
        return;

    default:
        return;
    }
}

bool ClientGameCycle::inputMouseDown() {
    if (InternetCycle::inputMouseDown()) {
        return true;
    }
    if (gameSaveButton.in(mouse)) {
        // Save current game field
        SavedFields::addField((Field)board);
        // Showing message of sucsessful saving
        savedInfo.reset();
        logAdditional("Saving field");
        return true;
    }
    // Normal turn
    board.clickClientCurrent(mouse);
    return false;
}

void ClientGameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    board.blit(window);
    letters.blit(window);

    // Draw game state
    switch (board.getState()) {
    case GameState::CurrentPlay:
        playersTurnsTexts[1].blit();
        break;

    case GameState::OpponentPlay:
        playersTurnsTexts[0].blit();
        break;

    case GameState::CurrentWin:
        looseText.blit();
        break;

    case GameState::OpponentWin:
        winText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
        break;
    }
    // Drawing upper dashboard
    exitButton.blit();
    gameSaveButton.blit();
    settings.blit();

    // Bliting game menu
    // menu.blit();

    // Messages
    savedInfo.blit();
    disconnectedBox.blit();
    termianatedBox.blit();

    // Bliting all to screen
    window.render();
}
