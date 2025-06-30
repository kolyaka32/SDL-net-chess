/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <sstream>
#include "baseGUI.hpp"


GUI::DynamicText::DynamicText(const Window& _target, const LanguagedText _texts,
    float _X, float _Y, float _height, Color _color, Aligment _aligment)
: posX(_X),
aligment(_aligment),
color(_color),
texts(_texts),
height(_height) {
    rect.y = WINDOW_HEIGHT * _Y - height / 2;
    setValues(_target);
}

GUI::DynamicText::~DynamicText() {
    SDL_DestroyTexture(texture);
}
