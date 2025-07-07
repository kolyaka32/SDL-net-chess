/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"

// Static class members
Board GameCycle::board;
Uint8 GameCycle::endState;

GameCycle::GameCycle(const App& _app)
: BaseCycle(_app),
letters(_app.window),
restartButton(_app.window, 0.5, 0.5, {"Restart", "Перезапустить", "Starten", "Перазапуск"}, 24, WHITE),
menuButton(_app.window, 0.5, 0.6, {"Exit to menu", "Выйти в меню", "Menü verlassen", "Выйсці ў меню"}, 24, WHITE),
playersTurnsTexts {
    {_app.window, 0.5, 0.1, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}, 24, WHITE},
    {_app.window, 0.5, 0.1, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}, 24, WHITE},
    {_app.window, 0.5, 0.1, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}, 24, WHITE},
    {_app.window, 0.5, 0.1, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}, 24, WHITE},
},
endBackplate(_app.window, 0.5, 0.5, 0.6, 0.3, 40, 5),
winText(_app.window, 0.5, 0.4, {"Win!", "Победа!", "Sieg!", "Перамога!"}, 30, WHITE),
firstWinText(_app.window, 0.5, 0.4, {"Fist player win!", "Первый игрок выйграл!", "Der erste Spieler hat gewonnen!", "Першы гулец выйграў!"}, 30, WHITE),
secondWinText(_app.window, 0.5, 0.4, {"Second player win!", "Второй игрок выйграл!", "Der zweite Spieler hat gewonnen!", "Другі гулец выйграў!"}, 30, WHITE),
looseText(_app.window, 0.5, 0.4, {"You loose...", "Вы проиграли...", "Sie haben verloren...", "Вы прайгралі..."}, 30, WHITE),
nobodyWinText(_app.window, 0.5, 0.4, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 30, WHITE) {
    endState = END_NONE;

    if (!isRestarted()) {
        board.reset();
    }
}

void GameCycle::inputMouseDown(App& _app) {
    if (exitButton.in(mouse)) {
        _app.startNextCycle(Cycle::Menu);
        stop();
        return;
    } else if (settings.click(mouse)) {
        // Updating location
        _app.window.updateTitle();
        restart();
    } else if (!settings.isActive()) {
        // Checking, if game start
        if (endState <= END_TURN) {
            // Clicking on field
            endState = board.click(_app.sounds, mouse);
            return;
        }
        // Starting waiting menu
        if (restartButton.in(mouse)) {
            // Restarting current game
            endState = END_NONE;

            // Resetting field
            board.reset();

            // Making sound
            _app.sounds.play(SND_RESET);
            return;
        }
        if (menuButton.in(mouse)) {
            // Going to menu
            _app.startNextCycle(Cycle::Menu);
            stop();
            return;
        }
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

    case SDLK_Q:
        // Quiting to menu
        _app.startNextCycle(Cycle::Menu);
        stop();
        return;
    }
}

void GameCycle::update(App& _app) {
    settings.update(_app);
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

    // Bliting game state, if need
    if (endState > END_TURN) {
        // Bliting end background
        endBackplate.blit(_app.window);

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
        restartButton.blit(_app.window);
        menuButton.blit(_app.window);
    }
    // Drawing setting menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
