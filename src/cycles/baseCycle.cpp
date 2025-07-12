/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseCycle.hpp"


// Base cycle class
BaseCycle::BaseCycle(const App& _app)
: exitButton(_app.window, 0.05, 0.05, IMG_GUI_QUIT_BUTTON),
settings(_app) {}

void BaseCycle::update(App& _app) {
    settings.update(_app);
}

void BaseCycle::inputMouseUp(App& _app) {
    settings.unClick();
}

void BaseCycle::inputMouseWheel(App& _app, float _wheelY) {
    settings.scroll(_app, mouse, _wheelY);
}
