/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::OneOptionBox::OneOptionBox(const Window& _window, float _X, float _Y, float _W, float _H,
    const LanguagedText&& _title, const LanguagedText&& _button)
: SubWindow(_window, _X, _Y, _W, _H),
title(_window, _X, _Y - _H/4, std::move(_title), 1, Height::SubTitle),
button(_window, _X, _Y + _H/4, std::move(_button)) {}

GUI::OneOptionBox::OneOptionBox(OneOptionBox&& _object) noexcept
: SubWindow(std::move(_object)),
title(std::move(_object.title)),
button(std::move(_object.button)) {}

GUI::Code GUI::OneOptionBox::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        if (button.in(_mouse)) {
            return Button1;
        }
        return Some;
    }
    return None;
}

void GUI::OneOptionBox::blit() const {
    if (active) {
        background.blit();
        title.blit();
        button.blit();
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
