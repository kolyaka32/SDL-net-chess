/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"
#include <cstdio>

using namespace GUI;


DynamicText::DynamicText(const Window& _target, const std::string (&_text)[LNG_count], float _height,
    float _X, float _Y, Color _color, ALIGNMENT_types _aligment)
: posX(_X), posY(_Y), aligment(_aligment), color(_color), text(_text), height(_height) {
    updateLocation(_target);
}

DynamicText::~DynamicText() {
    SDL_DestroyTexture(texture);
}

void DynamicText::updateTexture(const Window& _target) {
    // Clearing previous texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Creating surface with text
    texture = _target.createTexture(FNT_MAIN, height, currentText, 0, color);

    // Moving draw rect to new place
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = WINDOW_WIDTH * posX - (rect.w * aligment / 2);
    rect.y = WINDOW_HEIGHT * posY - rect.h / 2;
}

void DynamicText::updateLocationArgs(const Window& _target, ...) {
    // Getting arguments
    va_list args;
    va_start(args, _target);

    // Creating buffer for text
    vsprintf_s(currentText, 50, text[currentLanguage].c_str(), args);

    va_end(args);

    updateTexture(_target);
}

void DynamicText::updateLocation(const Window& _target) {
    // Finding need text for this language
    strcpy_s(currentText, 50, text[currentLanguage].c_str());

    updateTexture(_target);
}
