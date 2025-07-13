/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


// Static class members
Board GameCycle::board;
Uint8 GameCycle::endState;

GameCycle::GameCycle(const App& _app)
: BaseCycle(_app),
letters(_app.window),
menuRestartButton(_app.window, 0.5, 0.5, {"Restart", "Перезапустить", "Starten", "Перазапуск"}, 24, WHITE),
menuExitButton(_app.window, 0.5, 0.6, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}, 24, WHITE),
gameRestartButton(_app.window, 0.12, 0.05, IMG_GUI_RESTART_BUTTON),
playersTurnsTexts {
    {_app.window, 0.5, 0.1, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}, 24, WHITE},
    {_app.window, 0.5, 0.1, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}, 24, WHITE}
},
menuBackplate(_app.window, 0.5, 0.5, 0.6, 0.3, 40, 5),
firstWinText(_app.window, 0.5, 0.4, {"Fist player win!", "Первый игрок выйграл!", "Der erste Spieler hat gewonnen!", "Першы гулец выйграў!"}, 30, WHITE),
secondWinText(_app.window, 0.5, 0.4, {"Second player win!", "Второй игрок выйграл!", "Der zweite Spieler hat gewonnen!", "Другі гулец выйграў!"}, 30, WHITE),
nobodyWinText(_app.window, 0.5, 0.4, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 30, WHITE) {
    if (!isRestarted()) {
        // Resetting field
        endState = END_NONE;
        board.reset();
        // Starting main song (if wasn't started)
        _app.music.start(MUS_MAIN);
    }
}

void GameCycle::inputMouseDown(App& _app) {
    if (settings.click(mouse)) {
        return;
    }
    if (exitButton.in(mouse)) {
        stop();
        return;
    }
    if (gameRestartButton.in(mouse)) {
        // Restarting current game
        endState = END_NONE;
        board.reset();

        // Making sound
        _app.sounds.play(SND_RESET);
        return;
    }
    // Checking, if game start
    if (endState <= END_TURN) {
        // Clicking on field
        endState = board.click(_app.sounds, mouse);

        #if CHECK_CORRECTION
        if (endState != END_NONE) {
            SDL_Log("Turn of current player: from %u to %u", board.getPreviousTurn(), getPos((mouse.getX() - LEFT_LINE) / CELL_SIDE, (mouse.getY() - UPPER_LINE) / CELL_SIDE));
        }
        #endif
        return;
    }
    // Starting waiting menu
    if (menuRestartButton.in(mouse)) {
        // Restarting current game
        endState = END_NONE;
        board.reset();

        // Making sound
        _app.sounds.play(SND_RESET);
        return;
    }
    if (menuExitButton.in(mouse)) {
        // Going to menu
        stop();
        return;
    }
}

void GameCycle::inputKeys(App& _app, SDL_Keycode key) {
    // Searching for key press
    switch (key) {
    case SDLK_ESCAPE:
        // Clearing selection by escape
        if (board.isFigureSelected()) {
            board.resetSelection();
        // Or go to setting menu
        } else {
            settings.activate();
        }
        return;

    case SDLK_R:
        // Restarting game
        endState = END_NONE;
        board.reset();
        // Making sound
        _app.sounds.play(SND_RESET);
        return;

    case SDLK_Q:
        // Quiting to menu
        stop();
        return;
    }
}

void GameCycle::draw(const App& _app) const {
    // Bliting field
    board.blit(_app.window);

    // Draw surround letters
    letters.blit(_app.window);

    // Drawing player state
    playersTurnsTexts[board.currentTurn()].blit(_app.window);

    // Drawing buttons
    exitButton.blit(_app.window);
    gameRestartButton.blit(_app.window);

    // Bliting game state, if need
    if (endState > END_TURN) {
        // Bliting end background
        menuBackplate.blit(_app.window);

        // Bliting text with end state
        switch (endState) {
        case END_WIN:
            firstWinText.blit(_app.window);
            break;

        case END_LOOSE:
            secondWinText.blit(_app.window);
            break;

        case END_NOBODY:
            nobodyWinText.blit(_app.window);
            break;
        }

        // Blitting buttons
        menuRestartButton.blit(_app.window);
        menuExitButton.blit(_app.window);
    }
    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
