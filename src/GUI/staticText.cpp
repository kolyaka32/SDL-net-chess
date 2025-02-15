/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

//#include <cstdlib>
#include <cstdio>


#include "baseGUI.hpp"

using namespace GUI;

// Class of static text
StaticText::StaticText(Window& _target, const std::string (&_text)[LNG_count], float _height,
    float _X, float _Y, SDL_Color _color, ALIGNMENT_types _aligment) {
    // Creating texture of text
    texture = _target.createTexture(FNT_MAIN, _height, _text[currentLanguage].c_str(), 0, _color);

    // Updating rect height for correct button
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _X - (rect.w * _aligment / 2);
    rect.y = SCREEN_HEIGHT * _Y - rect.h / 2;
}

StaticText::~StaticText() {
    // Clearing text buffer
    SDL_DestroyTexture(texture);
}
