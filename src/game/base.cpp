/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "base.hpp"

//
GameCycle::GameCycle() : CycleTemplate(MUS_START_NONE) {
    endState = END_NONE;
}

//
GameCycle::~GameCycle() {}


// Example for getting keys input
bool GameCycle::getKeysInput(SDL_Keysym& key) {
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
    // Pause button
    /*if (settingButton.in(mouseX, mouseY)) {
        return 1;
    }*/

    // Checking, if game start
    if (endState <= END_TURN) {
        // Clicking on field
        endState = board.click((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE);
    } else {
        // Getting buttons clicks
        // Game restart
        if (data.textButtons[BTN_GAME_RESTART].in(mouseX, mouseY)) {
            // Restarting game
            endState = END_NONE;

            // Resetting field
            board.reset();

            // Making sound
            data.playSound(SND_RESET);
            return false;

        } else if (data.textButtons[BTN_GAME_MENU].in(mouseX, mouseY)) {
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
    data.texts[TXT_GAME_TURN_FIRST + board.currentTurn()].blit();

    // Bliting game state, if need
    if (endState > END_TURN) {
        // Bliting end background
        endBackplate.blit();

        // Bliting text with end state
        switch (endState) {
        case END_WIN:
            data.texts[TXT_END_WIN_1].blit();
            break;

        case END_LOOSE:
            data.texts[TXT_END_WIN_2].blit();
            break;

        case END_NOBODY:
            data.texts[TXT_END_NOBODY].blit();
            break;
        }

        // Blitting buttons
        data.textButtons[BTN_GAME_RESTART].blit();
        data.textButtons[BTN_GAME_MENU].blit();
    }

    // Bliting all to screen
    data.render();
}
