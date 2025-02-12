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
: posX(_X), posY(_Y), aligment(_aligment), color(_color) {
    TTF_Font* font = _target.getFont(FNT_MAIN);

    SDL_Surface *surface = TTF_RenderText_Solid(font, _text[currentLanguage].c_str(), _text[currentLanguage].size(), _color);
    texture = _target.createTexture(surface);

    // Updating rect height for correct button
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _X - (rect.w * _aligment / 2);
    rect.y = SCREEN_HEIGHT * _Y - rect.h / 2;
}

DynamicText::~DynamicText() {
    // Clearing text buffer
    SDL_DestroyTexture(texture);
}

void DynamicText::updateTexture(Window& _target) {
    // Creating surface with text
    SDL_Surface *surface = TTF_RenderText_Solid(font, currentText.c_str(), currentText.size(), color);
    texture = _target.createTexture(surface);

    // Moving draw rect to new place
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * posX - (rect.w * aligment / 2);
    rect.y = SCREEN_HEIGHT * posY - rect.h / 2;
}

void DynamicText::updateLocationArgs(Window& _target, ...) {
    // Clearing previous buffer
    /*if (bufferText) {
        delete[] bufferText;
        bufferText = nullptr;
    }

    // Finding need text for current language
    currentText = text[currentLanguage];
    for (LNG_types lan = LNG_ENGLISH; lan != currentLanguage; ++lan) {
        // Parsing text to it end
        for (; *start++;) {}
    }

    // Getting arguments
    va_list args;
    va_start(args, _target);

    // Getting size of string
    length = _vscprintf(start, args);

    // Creating buffer for text
    bufferText = new char[length];
    vsprintf(bufferText, start, args);

    va_end(args);*/

    updateTexture(_target);
}

//
void DynamicText::updateLocation(Window& _target) {
    // Clearing previous buffer
    /*if (bufferText) {
        delete[] bufferText;
        bufferText = nullptr;
    }

    // Finding need text for this language
    const char* start = text[currentLanguage];
    for (LNG_types lan = LNG_ENGLISH; lan != currentLanguage; ++lan) {
        // Parsing text to it end
        for (; *start++;) {}
    }
    // Getting need size
    length = strlen(start) + 1;

    // Creating buffer for text and copy it here
    bufferText = new char[length];
    sprintf(bufferText, start);*/

    updateTexture(_target);
}
