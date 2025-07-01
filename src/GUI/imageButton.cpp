/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::ImageButton::ImageButton(const Window& _target, float _X, float _Y, IMG_names _index) {
    // Setting base texture
    texture = _target.getTexture(_index);

    // Setting destination
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = WINDOW_WIDTH * _X - rect.w / 2;
    rect.y = WINDOW_HEIGHT * _Y - rect.h / 2;
}
