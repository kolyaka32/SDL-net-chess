/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


// Class of static text
GUI::StaticText::StaticText(const Window& _target, const std::string (&_text)[LNG_count],
    float _X, float _Y, float _height, Color _color, ALIGNMENT_types _aligment) {
    // Creating texture of text
    texture = _target.createTexture(FNT_MAIN, _height, _text[currentLanguage].c_str(), 0, _color);

    // Updating rect height for correct button
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SDL_roundf(WINDOW_WIDTH * _X - (rect.w * _aligment / 2));
    rect.y = SDL_roundf(WINDOW_HEIGHT * _Y - rect.h / 2);
}

GUI::StaticText::~StaticText() {
    SDL_DestroyTexture(texture);
}
