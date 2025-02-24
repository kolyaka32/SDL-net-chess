/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"

// Base cycle class
BaseCycle::BaseCycle() {}

void BaseCycle::update(App& _app) {
    settings.update(_app);
}

void BaseCycle::getAnotherInput(App& _app, const SDL_Event& event) {
    settings.getAnotherInput(_app, event);
}
