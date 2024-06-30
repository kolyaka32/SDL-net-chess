/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "pauseCycle.hpp"


GameCycle::GameCycle() : BaseCycle(MUS_START_NONE) {
    endState = END_NONE;
}

// Resetting music to menu theme
GameCycle::~GameCycle() {}


// Example for getting keys input
bool GameCycle::getKeysInput(const SDL_Keysym& key) {
    // Searching for key press
    switch (key.sym) {
    case SDLK_ESCAPE:
        // Clearing selection by escape
        board.resetSelection();
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
    // Buttons
    if (settingButton.in(mouseX, mouseY)) {
        runCycle<PauseCycle>();
        return false;
    } else if (exitButton.in(mouseX, mouseY)) {
        return true;
    }

    // Checking, if game start
    if (endState <= END_TURN) {
        // Clicking on field
        endState = board.click((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE);
    } else {
        // Getting buttons clicks
        // Game restart
        if (restartButton.in(mouseX, mouseY)) {
            // Restarting game
            endState = END_NONE;

            // Resetting field
            board.reset();

            // Making sound
            data.playSound(SND_RESET);
            return false;

        } else if (menuButton.in(mouseX, mouseY)) {
            // Going to menu
            return true;
        }
    }

    // None-return
    return false;
}

//
void GameCycle::draw() const {
    // Bliting field
    board.blit();

    // Draw surround letters
    letters.blit();

    // Drawing player state
    playersTurnsTexts[board.currentTurn()].blit();

    // Drawing buttons
    settingButton.blit();
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

    // Bliting all to screen
    data.render();
}
