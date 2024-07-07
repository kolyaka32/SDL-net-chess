/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "twoPlayer.hpp"


TwoPlayerGameCycle::TwoPlayerGameCycle() {
    music.start();
}

TwoPlayerGameCycle::~TwoPlayerGameCycle() {
    // Resetting music to menu theme
    data.playMusic(MUS_MENU_THEME);
}
