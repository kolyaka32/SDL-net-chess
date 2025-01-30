/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"

GameCycle::GameCycle() : BaseCycle(MUS_START_NONE) {
    endState = END_NONE;
}


// Example for getting keys input
bool GameCycle::getKeysInput(const SDL_Keysym& key) {
    // Searching for key press
    switch (key.sym) {
    case SDLK_ESCAPE:
        // Clearing selection by escape
        if (board.isFigureSelected()) {
            board.resetSelection();
        // Or go to setting menu
        } else {
            settings.activate();
        }
        return false;

    case SDLK_q:
        // Quiting to menu
        return true;

    default:
        // None-return
        return false;
    }
}

// Getting mouse clicking
bool GameCycle::getMouseInput() {
    if (exitButton.in(mouseX, mouseY)) {
        return true;
    } else if (settings.click(mouseX, mouseY)) {
        // Checking, if game start
        if (endState <= END_TURN) {
            // Clicking on field
            endState = board.click((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE);
        } else {
            // Starting waiting menu
            if (restartButton.in(mouseX, mouseY)) {
                // Restarting current game
                endState = END_NONE;

                // Resetting field
                board.reset();

                // Making sound
                data.playSound(SND_RESET);
            } else if (menuButton.in(mouseX, mouseY)) {
                // Going to menu
                return true;
            }
        }
    }
    return false;
}

void GameCycle::update() {
    musicOrder.update();
    settings.update();
}

void GameCycle::draw() const {
    // Bliting field
    board.blit();

    // Draw surround letters
    letters.blit();

    // Drawing player state
    playersTurnsTexts[board.currentTurn()].blit();

    // Drawing buttons
    exitButton.blit();

    // Bliting game state, if need
    if (endState > END_TURN) {
        // Bliting end background
        endBackplate.blit();

        // Bliting text with end state
        switch (endState) {
        case END_WIN:
            firstWinText.blit();
            break;

        case END_LOOSE:
            secondWinText.blit();
            break;

        case END_NOBODY:
            nobodyWinText.blit();
            break;
        }

        // Blitting buttons
        restartButton.blit();
        menuButton.blit();
    }
    // Drawing setting menu
    settings.blit();

    // Bliting all to screen
    data.render();
}
