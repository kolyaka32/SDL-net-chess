/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

//#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Slider class
Slider::Slider(Window& _target, float _X, float _Y, unsigned *_controlData,
    IMG_names _lineImage, IMG_names _buttonImage, unsigned _max)
: link(_controlData), maxValue(_max) {
    // Getting need texture
    texture = _target.getTexture(_lineImage);
    textureButton = _target.getTexture(_buttonImage);
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    SDL_GetTextureSize(textureButton, &buttonRect.w, &buttonRect.h);

    // Setting it to need place
    rect.x = SCREEN_WIDTH * _X - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _Y - rect.h / 2;
    buttonRect.y = SCREEN_HEIGHT * _Y - buttonRect.h / 2;
    buttonRect.x = rect.x + *link * rect.w / maxValue - buttonRect.w / 2;
}

void Slider::blit(Window& _target) const {
    _target.blit(texture, rect);
    _target.blit(textureButton, buttonRect);
}

void Slider::setValue(float mouseX) {
    // Setting new position
    buttonRect.x = mouseX;

    // Setting borders for position
    SET_MAX(buttonRect.x, rect.x + rect.w);
    SET_MIN(buttonRect.x, rect.x);

    buttonRect.x -= buttonRect.w / 2;

    // Setting new linked value
    *link = (buttonRect.x - rect.x + buttonRect.w / 2) * maxValue / rect.w;
}

bool Slider::scroll(float wheelY, float mouseX, float mouseY) {
    if (in(mouseX, mouseY)) {
        if (wheelY > 0) {
            setValue(buttonRect.x + buttonRect.w/2 + 8);
        } else {
            setValue(buttonRect.x + buttonRect.w/2 - 8);
        }
        return true;
    }
    return false;
}
