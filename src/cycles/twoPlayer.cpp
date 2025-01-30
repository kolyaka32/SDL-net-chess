/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "twoPlayer.hpp"


// Two player mode (standart game)
TwoPlayerGameCycle::TwoPlayerGameCycle() {
    musicOrder.start();
}

TwoPlayerGameCycle::~TwoPlayerGameCycle() {
    // Resetting music to menu theme
    data.playMusic(MUS_MENU_THEME);
}
