/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Base cycle class
BaseCycle::BaseCycle(const App& _app)
: exitButton{_app.window, 0.05, 0.05, IMG_GUI_QUIT_BUTTON},
settings{_app} {
    // Opening settings menu after restart
    if (isRestarted()) {
        settings.activate();
    }
}

void BaseCycle::update(App& _app) {
    settings.update(_app);
}

void BaseCycle::getAnotherInput(App& _app, const SDL_Event& event) {
    settings.getAnotherInput(_app, event);
}
