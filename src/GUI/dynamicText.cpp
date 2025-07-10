/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <sstream>
#include "baseGUI.hpp"


GUI::DynamicText::DynamicText(const Window& _target, float _X, float _Y,
    const LanguagedText _texts, float _height, Color _color, Aligment _aligment)
: posX(_X),
aligment(_aligment),
color(_color),
texts(_texts),
height(_height) {
    rect.y = WINDOW_HEIGHT * _Y - height / 2;
    // Creating surface with text
    texture = _target.createTexture(FNT_MAIN, height, texts.getString().c_str(), 0, color);

    // Moving draw rect to new place
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = WINDOW_WIDTH * posX - (rect.w * (unsigned)aligment / 2);
}

GUI::DynamicText::~DynamicText() {
    SDL_DestroyTexture(texture);
}
