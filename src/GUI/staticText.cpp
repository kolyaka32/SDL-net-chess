/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

// Class of static text
StaticText::StaticText(const char* _text, textHeight _height,
    float _X, float _Y, SDL_Color _color, ALIGNMENT_types _aligment)
: text(_text), posX(_X), posY(_Y), aligment(_aligment), color(_color), bufferText(nullptr) {
    font = data.createFont(_height);

    // Updating rect height for correct button
    updateLocation();

    // Adding item to global location update list
    data.updateList.add(this);
}

StaticText::~StaticText() {
    // Clearing text buffer
    if (bufferText) {
        delete[] bufferText;
        bufferText = nullptr;
    }
    SDL_DestroyTexture(texture);
}

void StaticText::updateTexture() {
    // Creating surface with text
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, bufferText, color);
    texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    SDL_FreeSurface(surface);
    // Moving draw rect to new place
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * posX - (rect.w * aligment / 2);
    rect.y = SCREEN_HEIGHT * posY - rect.h / 2;
}

void StaticText::updateLocationArgs(const unsigned count, ...) {
    // Clearing previous buffer
    if (bufferText) {
        delete[] bufferText;
        bufferText = nullptr;
    }

    // Finding need text for this language
    const char* start = text;
    for (Uint8 lan = LNG_ENGLISH; lan != data.language; ++lan) {
        // Parsing text to it end
        for (; *start++;) {}
    }
    // Getting arguments
    va_list args;
    va_start(args, count);

    // Getting size of string
    size_t size = _vscprintf(start, args);

    // Creating buffer for text
    bufferText = new char[size];
    vsprintf(bufferText, start, args);

    va_end(args);

    updateTexture();
}

//
void StaticText::updateLocation() {
    // Clearing previous buffer
    if (bufferText) {
        delete[] bufferText;
        bufferText = nullptr;
    }

    // Finding need text for this language
    const char* start = text;
    for (Uint8 lan = LNG_ENGLISH; lan != data.language; ++lan) {
        // Parsing text to it end
        for (; *start++;) {}
    }
    // Getting need size
    size_t size = strlen(start) + 1;

    // Creating buffer for text and copy it here
    bufferText = new char[size];
    sprintf(bufferText, start);

    updateTexture();
}
