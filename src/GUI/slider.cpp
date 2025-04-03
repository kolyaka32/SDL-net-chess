/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;


// Slider class
Slider::Slider(const Window& _target, float _X, float _Y, unsigned _startValue,
    IMG_names _lineImage, IMG_names _buttonImage, unsigned _max)
: maxValue(_max) {
    // Getting need texture
    texture = _target.getTexture(_lineImage);
    textureButton = _target.getTexture(_buttonImage);
    SDL_GetTextureSize(texture, nullptr, &rect.h);
    rect.w = _max;
    SDL_GetTextureSize(textureButton, &buttonRect.w, &buttonRect.h);

    // Setting it to need place
    rect.x = WINDOW_WIDTH * _X - rect.w / 2;
    rect.y = WINDOW_HEIGHT * _Y - rect.h / 2;
    buttonRect.y = WINDOW_HEIGHT * _Y - buttonRect.h / 2;
    buttonRect.x = rect.x + _startValue - buttonRect.w / 2;
}

void Slider::blit(const Window& _target) const {
    _target.blit(texture, rect);
    _target.blit(textureButton, buttonRect);
}

unsigned Slider::setValue(float _mouseX) {
    // Setting new position
    buttonRect.x = _mouseX;

    // Setting borders for position
    SET_MAX(buttonRect.x, rect.x + rect.w);
    SET_MIN(buttonRect.x, rect.x);

    buttonRect.x -= buttonRect.w / 2;

    // Setting new linked value
    return buttonRect.x - rect.x + buttonRect.w/2;
}

unsigned Slider::scroll(float _wheelY) {
    if (_wheelY > 0) {
        return setValue(buttonRect.x + buttonRect.w/2 + 8);
    } else {
        return setValue(buttonRect.x + buttonRect.w/2 - 8);
    }
    return 0;
}
