/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"

// Declaration of static objects
bool BaseCycle::keepSettings = false;

// Base cycle class
BaseCycle::BaseCycle(const Window& _target)
: exitButton{application.window, 0.05, 0.05, IMG_GUI_QUIT_BUTTON},
settings{application.window} {
    if (keepSettings) {
        // Opening settings menu after restart
        settings.activate();
        keepSettings = false;
    }
}

void BaseCycle::setKeepSettings() {
    keepSettings = true;
}

void BaseCycle::update(App& _app) {
    settings.update(_app);
}

void BaseCycle::getAnotherInput(App& _app, const SDL_Event& event) {
    settings.getAnotherInput(_app, event);
}
