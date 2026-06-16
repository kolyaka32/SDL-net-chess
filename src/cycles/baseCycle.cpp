/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


BaseCycle::BaseCycle(Window& _window)
: CycleTemplate(_window),
exitButton(window, 0.04, 0.05, 0.08, Textures::QuitButton),
settings(window) {}

bool BaseCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (exitButton.in(mouse)) {
        App::setNextCycle(Cycle::Menu);
        return true;
    }
    return false;
}

void BaseCycle::update() {
    settings.update();
}

void BaseCycle::inputMouseUp() {
    settings.unClick();
}

bool BaseCycle::inputKeys(const SDL_Keycode _key) {
    if (_key == SDLK_ESCAPE) {
        settings.activate();
        return true;
    }
    return false;
}

bool BaseCycle::inputMouseWheel(float _wheelY) {
    return settings.scroll(mouse, _wheelY);
}
