/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::OneOptionBox::OneOptionBox(const Window& _window, float _X, float _Y, float _W, float _H,
    const LanguagedText&& _title, const LanguagedText&& _button)
: Template(_window),
active(false),
background(_window, _X, _Y, _W, _H, _H*_window.getHeight()/4, 2.0),
title(_window, _X, _Y - _H/4, std::move(_title), 1, Height::SubTitle),
button(_window, _X, _Y + _H/4, std::move(_button)) {}

GUI::OneOptionBox::OneOptionBox(OneOptionBox&& _object) noexcept
: Template(_object.window),
active(_object.active),
background(std::move(_object.background)),
title(std::move(_object.title)),
button(std::move(_object.button)) {}

int GUI::OneOptionBox::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        if (button.in(_mouse)) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void GUI::OneOptionBox::activate() {
    active = true;
}

void GUI::OneOptionBox::reset() {
    active = false;
}

bool GUI::OneOptionBox::isActive() const {
    return active;
}

void GUI::OneOptionBox::blit() const {
    if (active) {
        background.blit();
        title.blit();
        button.blit();
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
