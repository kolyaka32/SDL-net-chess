/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Type box class
typeBox::typeBox(textHeight _height, float _x, float _y, const char* _text, ALIGNMENT_types _aligment, SDL_Color _color)
: color(_color), aligment(_aligment) {
    font = data.createFont(_height);
    textRect.x = SCREEN_WIDTH * _x;
    textRect.y = SCREEN_HEIGHT * _y - _height / 2;
    textRect.w = textRect.h = 0;

    // Copying text to caret
    length = strlen(_text);
    caret = SET_MAX(length, bufferSize);
    memcpy(buffer, _text, length);
    buffer[length] = '\0';

    // Creating first texture, if there was any text
    if (caret) {
        updateTexture();
    }

    // Creating background picture for typing
    SDL_QueryTexture(data.textures[IMG_GUI_TYPE_BOX], NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _x - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _y - rect.h / 2 + 2;
}

// Clearing rest texture
typeBox::~typeBox() {
    SDL_DestroyTexture(texture);
}

// Creating new texture
void typeBox::updateTexture() {
    // Creating surface from text
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, buffer, color);
    // Updating texture
    texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    SDL_FreeSurface(surface);

    // Resetting place of text with saving aligment
    textRect.x += textRect.w * aligment / 2;
    SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x -= textRect.w * aligment / 2;
}

// Write need string to buffer with ability to clear source
void typeBox::writeString(char* str, bool freeData) {
    // Inserting text from clipboard
    Uint8 clipboardSize = strlen(str);

    // Checking, if all clipboard can be placed in buffer
    if (clipboardSize > bufferSize - length) {
        clipboardSize = bufferSize - length;
    }

    // Moving part after caret at end
    for (Sint8 i = length; i >= caret; --i) {
        buffer[i + clipboardSize] = buffer[i];
    }

    // Coping main clipboard text
    for (Uint8 i=0; i < clipboardSize; ++i) {
        buffer[caret + i] = str[i];
    }

    length += clipboardSize;
    caret += clipboardSize;

    updateTexture();

    if (freeData) {
        SDL_free(str);
    }
}

// Getting press of need KeyCode
void typeBox::press(SDL_Keycode code) {
    static SDL_Keycode preCode;

    // Switching between extra input options
    switch (code) {
    // Functions for deleting text
    case SDLK_BACKSPACE:
        // Coping after caret
        if (caret > 0) {
            for (Uint8 t = --caret; t <= length; ++t) {
                buffer[t] = buffer[t+1];
            }
            length--;
        }
        break;

    case SDLK_DELETE:
        // Coping after caret
        if (caret < length) {
            for (Uint8 t = caret + 1; t <= length; ++t) {
                buffer[t] = buffer[t+1];
            }
            length--;
        }
        break;

    // Moving caret
    case SDLK_LEFT:
        if (caret > 1) {
            std::swap(buffer[caret], buffer[caret - 1]);
            caret--;
        }
        break;

    case SDLK_RIGHT:
        if (caret + 1 < length) {
            std::swap(buffer[caret], buffer[caret + 1]);
            caret++;
        }
        break;

    // Special keys for faster caret move
    case SDLK_END:
    case SDLK_PAGEDOWN:
        // Copy all after caret
        for (Uint8 t = caret; t < length; ++t) {
            buffer[t] = buffer[t+1];
        }
        caret = length - 1;
        buffer[caret] = '|';
        swapCaret = ' ';
        break;

    case SDLK_HOME:
    case SDLK_PAGEUP:
        // Copy all before caret
        for (Uint8 t = caret; t > 0; --t) {
            buffer[t+1] = buffer[t];
        }
        caret = 0;
        buffer[caret] = '|';
        swapCaret = ' ';
        break;

    // Inserting text from clipboard
    case SDLK_PASTE:
        writeString(SDL_GetClipboardText(), true);
        break;

    case SDLK_v:
        if (preCode == SDLK_LCTRL) {
            writeString(SDL_GetClipboardText(), true);
        }
        break;

    case SDLK_LCTRL:
        if (preCode == SDLK_v) {
            writeString(SDL_GetClipboardText(), true);
        }
        break;
    }
    // Updating texture after modifiying text
    updateTexture();
    preCode = code;
}

// Select last letter to create writing symbol
void typeBox::select() {
    // Setting symbol of caret to line
    buffer[length] = '|';
    // Resetting swapping caret
    swapCaret = ' ';

    // Moving end of string
    caret = length++;
    buffer[length] = '\0';
    updateTexture();

    // Starting using keyboard
    SDL_StartTextInput();
}

// Clear selection of writing symbol
void typeBox::removeSelect() {
    // Stoping entering any letters
    SDL_StopTextInput();

    for (Uint8 t = caret; t <= length; t++) {
        buffer[t] = buffer[t+1];
    }
    length--;
    updateTexture();
}

// Swapping caret with writing symbol to space and back
void typeBox::updateCaret() {
    std::swap(buffer[caret], swapCaret);
    updateTexture();
}

// Overrided function for draw text and backplate at screen
void typeBox::blit() const {
    // Rendering background picture for better typing
    SDL_RenderCopy(data.renderer, data.textures[IMG_GUI_TYPE_BOX], NULL, &rect);

    // Rendering text
    SDL_RenderCopy(data.renderer, texture, NULL, &textRect);
}
