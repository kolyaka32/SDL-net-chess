/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Slider class
Slider::Slider(float _X, float _Y, unsigned *_controlData,
    IMG_names _lineImage, IMG_names _buttonImage, unsigned _max)
: link(_controlData), maxValue(_max) {
    // Getting need texture
    texture = data.textures[_lineImage];
    textureButton = data.textures[_buttonImage];
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);

    // Setting it to need place
    rect.x = SCREEN_WIDTH * _X - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _Y - rect.h / 2;
    destButton.y = SCREEN_HEIGHT * _Y - destButton.h / 2;
    destButton.x = rect.x + *link * rect.w / maxValue - destButton.w / 2;
}

// Blitting all slider to screen
void Slider::blit() const {
    SDL_RenderCopy(data.renderer, texture, NULL, &rect);
    SDL_RenderCopy(data.renderer, textureButton, NULL, &destButton);
}

// Setting new value of slider
void Slider::setValue(const int mouseX) {
    // Getting new position
    destButton.x = mouseX;
    // Setting borders for position
    SET_MAX(destButton.x, rect.x + rect.w);
    SET_MIN(destButton.x, rect.x);

    destButton.x -= destButton.w / 2;

    // Setting new linked value
    *link = (destButton.x - rect.x + destButton.w / 2) * maxValue / rect.w;
}


bool Slider::scroll(const Sint32 wheelY, const int mouseX, const int mouseY) {
    if (in(mouseX, mouseY)) {
        if (wheelY > 0) {
            setValue(destButton.x + destButton.w/2 + 8);
        } else {
            setValue(destButton.x + destButton.w/2 - 8);
        }
        return true;
    }
    return false;
}
