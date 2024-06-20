/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdlib>
#include <cstring>
#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Type box class
TypeBox::TypeBox(textHeight _height, float _x, float _y, const char* _text, ALIGNMENT_types _aligment, SDL_Color _color)
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
TypeBox::~TypeBox() {
    SDL_DestroyTexture(texture);
}

// Creating new texture
void TypeBox::updateTexture() {
    // Creating main surface from all text
    SDL_Surface* mainSurface = TTF_RenderUTF8_Solid(font, buffer, color);

    //
    if (selectLength) {
        char t = '\0';
        SDL_Surface* inverseSurface = nullptr;
        SDL_Rect inverseRect = {0, 0, 0, 0};

        if (selectLength > 0) {
            std::swap(buffer[caret+1], t);
            TTF_SizeUTF8(font, buffer, &inverseRect.x, &inverseRect.h);
            std::swap(buffer[caret+1], t);
            std::swap(buffer[caret + selectLength+1], t);
            inverseSurface = TTF_RenderUTF8_Shaded(font, buffer+caret+1, WHITE, color);
            std::swap(buffer[caret + selectLength+1], t);
        } else {
            std::swap(buffer[caret + selectLength], t);
            TTF_SizeUTF8(font, buffer, &inverseRect.x, &inverseRect.h);
            std::swap(buffer[caret + selectLength], t);
            std::swap(buffer[caret], t);
            inverseSurface = TTF_RenderUTF8_Shaded(font, buffer + caret + selectLength, WHITE, color);
            std::swap(buffer[caret], t);
        }
        inverseRect.w = inverseSurface->w;
        SDL_BlitSurface(inverseSurface, NULL, mainSurface, &inverseRect);
        SDL_FreeSurface(inverseSurface);
    }

    // Updating texture
    texture = SDL_CreateTextureFromSurface(data.renderer, mainSurface);
    SDL_FreeSurface(mainSurface);

    // Resetting place of text with saving aligment
    textRect.x += textRect.w * aligment / 2;
    SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x -= textRect.w * aligment / 2;
}

// Returning text
const char* TypeBox::getString() const {
    return buffer;
}

// Write need string to buffer with ability to clear source
void TypeBox::writeString(const char* str) {
    deleteSelected();

    // Inserting text from clipboard
    int clipboardSize = strlen(str);

    // Checking, if all clipboard can be placed in buffer
    if (clipboardSize > bufferSize - length) {
        clipboardSize = bufferSize - length;
    }

    // Moving part after caret at end
    for (int i = length; i >= caret; --i) {
        buffer[i + clipboardSize] = buffer[i];
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
void TypeBox::writeClipboard() {
    deleteSelected();
    char* clippboard = SDL_GetClipboardText();
    writeString(clippboard);
    SDL_free(clippboard);
}

// Copying selected text to clipboard
void TypeBox::copyToClipboard() {
    if (selectLength < 0) {
        memcpy(&clipboardText, buffer + caret + selectLength, abs(selectLength));
    } else {
        memcpy(&clipboardText, buffer + caret + 1, abs(selectLength));
    }
    clipboardText[abs(selectLength)] = '\0';
    SDL_SetClipboardText(clipboardText);
}

void TypeBox::selectAll() {
    char t = buffer[caret];
    for (int i=caret-1; i >= 0; --i) {
        buffer[i+1] = buffer[i];
    }
    buffer[0] = t;
    caret = 0;
    selectLength = length-1;
}

void TypeBox::deleteSelected() {
    if (selectLength < 0) {
        for (int i=caret; i <= length; ++i) {
            buffer[i + selectLength] = buffer[i];
        }
        caret += selectLength;
        length += selectLength;
    } else {
        for (int i=caret+1; i <= length - selectLength; ++i) {
            buffer[i] = buffer[i + selectLength];
        }
        length -= selectLength;
    }
    selectLength = 0;
}

// Getting press of need KeyCode
void TypeBox::press(SDL_Keycode code) {
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
        if (preCode == SDLK_LSHIFT) {
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
        if (preCode == SDLK_LSHIFT) {
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

    case SDLK_v:
        if (preCode == SDLK_LCTRL) {
            writeClipboard();
        } else {
            preCode = code;
            return;
        }
        break;

    case SDLK_c:
        if (preCode == SDLK_LCTRL) {
            copyToClipboard();
        } else {
            preCode = code;
            return;
        }
        break;

    case SDLK_a:
        if (preCode == SDLK_LCTRL) {
            selectAll();
        } else {
            preCode = code;
            return;
        }
        break;

    default:
        preCode = code;
        return;
    }
    // Updating texture after modifiying text
    updateTexture();
}

// Check, if need reset previous code
void TypeBox::resetPress(SDL_Keycode code) {
    if (code == preCode) {
        preCode = 0;
    }
}

// Select last letter to create writing symbol
void TypeBox::select(int _mouseX) {
    // Resetting swapping caret
    swapCaret = ' ';
    selectLength = 0;
    preCode = 0;

    TTF_MeasureUTF8(font, buffer, _mouseX - textRect.x, nullptr, &caret);

    // Moving all string
    for (int i=length; i >= caret; --i) {
        buffer[i+1] = buffer[i];
    }
    length++;

    buffer[caret] = '|';
    updateTexture();

    // Starting using keyboard
    SDL_StartTextInput();
}

// Clear selection of writing symbol
void TypeBox::removeSelect() {
    // Stoping entering any letters
    SDL_StopTextInput();

    // Clearing enter symbol
    for (int t = caret; t <= length; t++) {
        buffer[t] = buffer[t+1];
    }
    selectLength = 0;
    length--;
    updateTexture();
}

// Swapping caret with writing symbol to space and back
void TypeBox::updateCaret() {
    std::swap(buffer[caret], swapCaret);
    updateTexture();
}

// Selecting text
void TypeBox::updateSelection(int _mouseX) {
    // Check on borders
    TTF_MeasureUTF8(font, buffer, _mouseX - textRect.x, nullptr, &selectLength);
    if (selectLength <= caret) {
        SET_MIN(selectLength, 0);
        selectLength -= caret;
    } else {
        selectLength -= (caret+1);
    }
    updateTexture();
}

// Overrided function for draw text and backplate at screen
void TypeBox::blit() const {
    // Rendering background picture for better typing
    SDL_RenderCopy(data.renderer, data.textures[IMG_GUI_TYPE_BOX], NULL, &rect);

    // Rendering text
    SDL_RenderCopy(data.renderer, texture, NULL, &textRect);
}
