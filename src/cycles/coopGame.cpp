/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "coopGame.hpp"


TwoPlayerGameCycle::TwoPlayerGameCycle(Window& _window)
: GameCycle(_window),
menu(_window) {
    if (!isRestarted()) {
        menu.reset();
    }
    logger.additional("Start coop game cycle");
}

bool TwoPlayerGameCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (gameSaveButton.in(mouse)) {
        // Save current game field
        menu.addField((Field)board);
        // Showing message of sucsessful saving
        savedInfo.reset();
        logger.additional("Saving current field");
        return true;
    }
    if (gameMenuButton.in(mouse)) {
        // Starting game menu
        menu.activate();
        return true;
    }
    // Check if in menu
    if (menu.isActive()) {
        if (const Field* f = menu.click(mouse)) {
            board = *f;
            menu.reset();
            // Making sound
            audio.sounds.play(Sounds::Reset);
            logger.additional("Selecting new field");
        }
        return true;
    }
    // Normal turn
    board.clickCooperative(mouse);

    return false;
}

void TwoPlayerGameCycle::inputMouseUp() {
    GameCycle::inputMouseUp();
    menu.unclick();
}

bool TwoPlayerGameCycle::inputMouseWheel(float _wheelY) {
    if (BaseCycle::inputMouseWheel(_wheelY)) {
        return true;
    }
    if (menu.scroll(_wheelY)) {
        return true;
    }
    return false;
}

bool TwoPlayerGameCycle::inputKeys(SDL_Keycode _key) {
    if (_key == SDLK_ESCAPE) {
        // Closing top open object
        if (menu.escape()) {
            return true;
        }
    }
    return GameCycle::inputKeys(_key);
}

void TwoPlayerGameCycle::update() {
    GameCycle::update();
    menu.update();
}

void TwoPlayerGameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    board.blit(window);
    letters.blit(window);

    // Draw game state
    switch (board.getState()) {
    case GameState::CurrentPlay:
        currentTurnText.blit();
        break;

    case GameState::OpponentPlay:
        opponentTurnText.blit();
        break;

    case GameState::CurrentWin:
        firstWinText.blit();
        break;

    case GameState::OpponentWin:
        secondWinText.blit();
        break;

    case GameState::NobodyWin:
        nobodyWinText.blit();
        break;

    default:
        break;
    }
    // Draw menu with options to start
    menu.blit();

    // Drawing upper dashboard
    exitButton.blit();
    gameMenuButton.blit();
    gameSaveButton.blit();
    savedInfo.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}
