/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::OneOptionBox::OneOptionBox(const Window& _window, const LanguagedText&& _title,
    const LanguagedText&& _buttonText)
: Template(_window),
mainText(_window, 0.5, 0.45, std::move(_title), 1, Height::SubTitle),
button(_window, 0.5, 0.55, std::move(_buttonText)),
background(_window, 0.5, 0.5, 0.9, 0.2, 5.0, 1.0) {}

GUI::OneOptionBox::OneOptionBox(OneOptionBox&& _object) noexcept
: Template(_object.window),
active(_object.active),
mainText(std::move(_object.mainText)),
button(std::move(_object.button)),
background(std::move(_object.background)) {}

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
        button.blit();
        mainText.blit();
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
