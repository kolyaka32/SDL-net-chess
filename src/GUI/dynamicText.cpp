/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

//#include <cstdlib>
#include <cstdio>


#include "baseGUI.hpp"

using namespace GUI;

// Class of static text
DynamicText::DynamicText(Window& _target, const std::string (&_text)[LNG_count], float _height,
    float _X, float _Y, SDL_Color _color, ALIGNMENT_types _aligment)
: posX(_X), posY(_Y), aligment(_aligment), color(_color), text(_text), height(_height) {
    updateLocation(_target);
}

DynamicText::~DynamicText() {
    // Clearing text buffer
    SDL_DestroyTexture(texture);
}

void DynamicText::updateTexture(Window& _target) {
    // Clearing previous texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Creating surface with text
    texture = _target.createTexture(FNT_MAIN, height, currentText, currentLength, color);

    // Moving draw rect to new place
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * posX - (rect.w * aligment / 2);
    rect.y = SCREEN_HEIGHT * posY - rect.h / 2;
}

void DynamicText::updateLocationArgs(Window& _target, ...) {
    // Getting arguments
    va_list args;
    va_start(args, _target);

    // Creating buffer for text
    vsprintf_s(currentText, 50, text[currentLanguage].c_str(), args);
    currentLength = strlen(currentText);

    va_end(args);

    updateTexture(_target);
}

//
void DynamicText::updateLocation(Window& _target) {
    // Finding need text for this language
    currentLength = text[currentLanguage].size();
    sprintf_s(currentText, 50, text[currentLanguage].c_str());

    updateTexture(_target);
}
