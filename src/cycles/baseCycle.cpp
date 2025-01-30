/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"

// Base cycle class
BaseCycle::BaseCycle(MUS_names _music) : music(_music) {
    // Resetting values
    selectedBox = 0;

    // Starting playing need music
    if (music) {
        data.playMusic(music);
    }
}

void BaseCycle::update() {
    settings.update();
}

bool BaseCycle::getAnotherInput(const SDL_Event& event) {
    settings.getAnotherInput(event);
    return false;
}
