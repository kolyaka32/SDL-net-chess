/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"


GameCycle::GameCycle(Window& _window)
: BaseCycle(_window),
board(_window),
letters(_window),
gameSaveButton(_window, 0.88, 0.05, 0.08, Textures::SaveButton),
gameMenuButton(_window, 0.12, 0.05, 0.08, Textures::MenuButton),
savedInfo(_window, 0.5, 0.12, {"Game saved", "Игра сохранена", "Spiel gespeichert", "Гульня захавана"}),
playersTurnsTexts {
    {_window, 0.5, 0.05, {"First player turn", "Ход первого игрока", "Der Zug des ersten Spielers", "Ход першага гульца"}},
    {_window, 0.5, 0.05, {"Second player turn", "Ход второго игрока", "Zug des zweiten Spielers", "Ход другога гульца"}}
},
firstWinText(_window, 0.5, 0.05, {"First win", "Первый победил", "Der erste hat gewonnen", "Першы перамог"}, 1),
secondWinText(_window, 0.5, 0.05, {"Second win", "Второй победил", "Der zweite hat gewonnen", "Другі перамог"}, 1),
nobodyWinText(_window, 0.5, 0.05, {"Nobody win", "Ничья", "Unentschieden", "Чые"}, 1) {
    if (!isRestarted()) {
        // Resetting field
        //endState = END_NONE;
        board.reset();
    }
    // Starting main song (if wasn't started)
    audio.music.startFading(Music::Main);
}

void GameCycle::inputKeys(SDL_Keycode _key) {
    // Quiting to menu
    if (_key == SDLK_Q) {
        App::setNextCycle(Cycle::Menu);
    }
}

void GameCycle::update() {
    BaseCycle::update();
    savedInfo.update();
}
