/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "twoPlayer.hpp"


// Two player mode (standart game)
TwoPlayerGameCycle::TwoPlayerGameCycle(const Window& _target)
: GameCycle(_target) {
    //musicOrder.start();
}

TwoPlayerGameCycle::~TwoPlayerGameCycle() {
    // Resetting music to menu theme
    //data.playMusic(MUS_MENU_THEME);
}
