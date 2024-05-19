/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "twoPlayer.hpp"

//
TwoPlayerGameCycle::TwoPlayerGameCycle() {
    // Starting playing menu theme
    data.playMusic(MUS_MAIN_THEME);
}

//
TwoPlayerGameCycle::~TwoPlayerGameCycle() {
    // Starting playing menu theme
    data.playMusic(MUS_MENU_THEME);
}
