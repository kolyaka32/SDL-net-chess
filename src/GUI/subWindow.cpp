/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::SubWindow::SubWindow(const Window& _window, float _X, float _Y, float _W, float _H)
: Template(_window),
active(false),
background(_window, _X, _Y, _W, _H, (_H+_W)*_window.getHeight()/16, 2.0) {}

GUI::SubWindow::SubWindow(SubWindow&& _object) noexcept
: Template(_object.window),
active(_object.active),
background(std::move(_object.background)) {}

void GUI::SubWindow::reset() {
    active = false;
}

void GUI::SubWindow::open() {
    active = true;
}

void GUI::SubWindow::close() {
    active = false;
}

bool GUI::SubWindow::isOpen() const {
    return active;
}

bool GUI::SubWindow::escape() {
    if (active) {
        active = false;
        return true;
    }
    return false;
}

void GUI::SubWindow::toggle() {
    active ^= true;
}

void GUI::SubWindow::blit() const {
    if (active) {
        background.blit();
    }
}
