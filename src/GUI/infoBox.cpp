/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::InfoBox::InfoBox(const Window& _target, float _X, float _Y, const LanguagedText texts,
    float _size, Color _color, Aligment _aligment)
: StaticText(_target, _X, _Y, texts, _size, _color, _aligment) {
    // Resetting transperance
    SDL_SetTextureAlphaMod(texture, 0);
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
