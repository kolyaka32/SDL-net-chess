/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"

// Declaration of global objects
//const GUI::ImageButton BaseCycle::exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};
//SettingsMenu BaseCycle::settings;

// Base cycle class
BaseCycle::BaseCycle(const Window& _target)
: exitButton{_target, 0.05, 0.05, IMG_GUI_QUIT_BUTTON},
settings(_target) {}

void BaseCycle::update(App& _app) {
    settings.update(_app);
}

void BaseCycle::getAnotherInput(App& _app, const SDL_Event& event) {
    settings.getAnotherInput(_app, event);
}
