/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "twoPlayer.hpp"


// Two player mode (standart game)
TwoPlayerGameCycle::TwoPlayerGameCycle(const App& _app)
: GameCycle(_app) {
    // Starting main music
    if (!isRestarted()) {
        _app.music.start(MUS_MAIN);
    }
}

