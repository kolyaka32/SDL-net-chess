/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::InfoBox::InfoBox(const Window& _window, float _X, float _Y, const LanguagedText&& _texts,
    float _size, Color _color, Aligment _aligment)
: HighlightedStaticText(_window, _X, _Y, std::move(_texts), 2, _size, _color, _aligment) {
    // Resetting transperance
    SDL_SetTextureAlphaMod(texture, 0);
}

GUI::InfoBox::InfoBox(InfoBox&& _object) noexcept
: HighlightedStaticText(std::move(_object)),
counter(_object.counter) {
    SDL_SetTextureAlphaModFloat(texture, (float)counter/maxCounter);
}

void GUI::InfoBox::update() {
    if (counter) {
        // Setting text to be less and less visible
        SDL_SetTextureAlphaModFloat(texture, (float)counter/maxCounter);
        counter--;
    }
}

void GUI::InfoBox::reset() {
    counter = maxCounter;
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
