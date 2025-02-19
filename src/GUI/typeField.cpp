/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdlib>
#include <algorithm>
#include "baseGUI.hpp"

using namespace GUI;


// Type field class
TypeField::TypeField(Window& _target, float _height, float _x, float _y, const char* _text, ALIGNMENT_types _aligment, SDL_Color _color)
: target(_target), posX(SCREEN_WIDTH*_x), aligment(_aligment), textColor(_color), font(_target.createFontCopy(FNT_MAIN, _height)) {
    // Setting rect
    rect = {0, SCREEN_HEIGHT*_y-_height/2-1, 0, 0};

    // Copying text to caret
    length = strlen(_text);
    SET_MAX(length, bufferSize);
    memcpy(buffer, _text, length);

    // Creating first texture, if there was any text
    if (length) {
        updateTexture();
    }
}

TypeField::~TypeField() {
    // Clearing rest texture
    SDL_DestroyTexture(texture);

    // Clearing font
    TTF_CloseFont(font);
}

// Creating new texture
void TypeField::updateTexture() {
    // Clearing previous
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Creating main surface from all text
    SDL_Surface* mainSurface = TTF_RenderText_Solid(font, buffer, length, textColor);

    // Inversing selected part of text, if need
    if (selectLength) {
        SDL_Surface* inverseSurface = nullptr;
        SDL_Rect inverseRect = {0, 0, 0, 0};

        if (selectLength > 0) {
            TTF_GetStringSize(font, buffer, caret+1, &inverseRect.x, nullptr);
            inverseSurface = TTF_RenderText_Solid(font, buffer + caret + 1, selectLength, WHITE);
        } else {
            if (-selectLength == caret) {
                inverseRect.x = 0;
            } else {
                TTF_GetStringSize(font, buffer, caret + selectLength, &inverseRect.x, nullptr);
            }
            inverseSurface = TTF_RenderText_Solid(font, buffer + caret + selectLength, -selectLength, WHITE);
        }
        // Blitting inverse suface on main
        inverseRect.w = inverseSurface->w;
        inverseRect.h = inverseSurface->h;
        
        // Filling area with black color
        SDL_FillSurfaceRect(mainSurface, &inverseRect, 0x1);
        SDL_BlitSurface(inverseSurface, NULL, mainSurface, &inverseRect);
        SDL_DestroySurface(inverseSurface);
    }

    // Updating texture
    texture = target.createTexture(mainSurface);
    SDL_DestroySurface(mainSurface);

    // Resetting place of text with saving aligment
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = SDL_floorf(posX - rect.w * aligment / 2);
}

// Returning current text
const char* TypeField::getString() const {
    return buffer;
}

// Write need string to buffer with ability to clear source
void TypeField::writeString(const char* str) {
    deleteSelected();

    // Inserting text from clipboard
    int clipboardSize = strlen(str);

    // Checking, if all clipboard can be placed in buffer
    if (clipboardSize > bufferSize - length) {
        clipboardSize = bufferSize - length;
    }

    // Moving part after caret at end
    for (size_t i = length+1; i > caret; --i) {
        buffer[i + clipboardSize-1] = buffer[i-1];
    }

    // Coping main clipboard text
    for (int i=0; i < clipboardSize; ++i) {
        buffer[caret + i] = str[i];
    }

    length += clipboardSize;
    caret += clipboardSize;
    updateTexture();
}

// Getting clippboard content
void TypeField::writeClipboard() {
    deleteSelected();
    char* clippboard = SDL_GetClipboardText();
    writeString(clippboard);
    SDL_free(clippboard);
}

// Copying selected text to clipboard
void TypeField::copyToClipboard() {
    if (selectLength < 0) {
        memcpy(&clipboardText, buffer + caret + selectLength, abs(selectLength));
    } else {
        memcpy(&clipboardText, buffer + caret + 1, abs(selectLength));
    }
    clipboardText[abs(selectLength)] = '\0';
    SDL_SetClipboardText(clipboardText);
}

void TypeField::selectAll() {
    char t = buffer[caret];
    for (int i=caret-1; i >= 0; --i) {  ////////////////////////////////////////////// Rewrite
        buffer[i+1] = buffer[i];
    }
    buffer[0] = t;
    caret = 0;
    selectLength = length-1;
}

void TypeField::deleteSelected() {
    if (selectLength) {
        if (selectLength < 0) {
            for (size_t i=caret; i <= length; ++i) {
                buffer[i + selectLength] = buffer[i];
            }
            caret += selectLength;
            length += selectLength;
        } else {        ////////////////////////////////// Strange
            for (int i=caret+1; i <= length - selectLength; ++i) {
                buffer[i] = buffer[i + selectLength];
            }
            length -= selectLength;
        }
        selectLength = 0;
    }
}

// Getting press of need KeyCode
void TypeField::press(SDL_Keycode code) {
    // Getting current shft and control state
    SDL_Keymod keyMods = SDL_GetModState();

    // Switching between extra input options
    switch (code) {
    // Functions for deleting text
    case SDLK_BACKSPACE:
        // Coping after caret
        if (selectLength == 0) {
            if (caret == 0) {
                return;
            }
            selectLength = -1;
        }
        deleteSelected();
        break;

    case SDLK_DELETE:
        // Coping after caret
        if (selectLength == 0) {
            if (caret == length - 1) {
                return;
            }
            selectLength = 1;
        }
        deleteSelected();
        break;

    // Moving caret
    case SDLK_LEFT:
        if (keyMods & SDL_KMOD_SHIFT) {
            if (selectLength > -caret) {
                selectLength--;
            }
        } else {
            selectLength = 0;
            if (caret > 0) {
                std::swap(buffer[caret], buffer[caret - 1]);
                caret--;
            }
        }
        break;

    case SDLK_RIGHT:
        if (keyMods & SDL_KMOD_SHIFT) {
            if (selectLength < length - caret - 1) {
                selectLength++;
            }
        } else {
            selectLength = 0;
            if (caret + 1 < length) {
                std::swap(buffer[caret], buffer[caret + 1]);
                caret++;
            }
        }
        break;

    // Special keys for faster caret move
    case SDLK_END:
    case SDLK_PAGEDOWN:
        selectLength = 0;
        // Copy all after caret
        for (int t = caret; t < length; ++t) {
            buffer[t] = buffer[t+1];
        }
        caret = length - 1;
        buffer[caret] = '|';
        swapCaret = ' ';
        break;

    case SDLK_HOME:
    case SDLK_PAGEUP:
        selectLength = 0;
        // Copy all before caret
        for (int t = caret-1; t >= 0; --t) {
            buffer[t+1] = buffer[t];
        }
        caret = 0;
        buffer[caret] = '|';
        swapCaret = ' ';
        break;

    // Clipboard
    case SDLK_PASTE:
        writeClipboard();
        break;

    case SDLK_COPY:
        copyToClipboard();
        break;

    case SDLK_V:
        if (keyMods & SDL_KMOD_CTRL) {
            writeClipboard();
        }
        break;

    case SDLK_C:
        if (keyMods & SDL_KMOD_CTRL) {
            copyToClipboard();
        }
        break;

    case SDLK_A:
        if (keyMods & SDL_KMOD_CTRL) {
            selectAll();
        }
        break;

    default:
        return;
    }
    // Updating texture after modifiying text
    updateTexture();
}

// Select last letter to create writing symbol
void TypeField::select(float _mouseX) {
    // Resetting swapping caret
    swapCaret = ' ';
    selectLength = 0;

    // Getting current mouse position at text
    TTF_MeasureString(font, buffer, length, _mouseX-rect.x, NULL, &caret);

    // Moving all string
    for (size_t i=length+1; i > caret; --i) {
        buffer[i] = buffer[i-1];
    }
    length++;

    buffer[caret] = '|';
    updateTexture();

    // Starting using keyboard
    target.startTextInput();
}

// Clear selection of writing symbol
void TypeField::removeSelect() {
    // Stoping entering any letters
    target.stopTextInput();

    // Clearing enter symbol
    for (size_t t = caret; t <= length; t++) {
        buffer[t] = buffer[t+1];
    }
    selectLength = 0;
    length--;
    updateTexture();
}

// Swapping caret with writing symbol to space and back
void TypeField::updateCaret() {
    if (SDL_GetTicks() > needSwap) {
        std::swap(buffer[caret], swapCaret);
        updateTexture();

        // Updating timer
        needSwap = SDL_GetTicks() + 500;
    }
}

// Selecting text
void TypeField::updateSelection(float _mouseX) {
    // Check on borders
    size_t measure;
    TTF_MeasureString(font, buffer, length, _mouseX-rect.x, NULL, &measure);

    if (measure <= caret) {
        selectLength = measure - caret;
    } else {
        selectLength = measure - (caret+1);
    }
    updateTexture();
}
