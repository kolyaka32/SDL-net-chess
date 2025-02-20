/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */


#include "baseGUI.hpp"

using namespace GUI;


// Button class
ImageButton::ImageButton(const Window& _target, float _x, float _y, IMG_names _index) {
    // Setting base texture
    texture = _target.getTexture(_index);

    // Setting destination
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _x - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _y - rect.h / 2;
}
