/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"
#include <cstdlib>
#include <algorithm>

using namespace GUI;


// Type field class
template <unsigned bufferSize>
TypeField<bufferSize>::TypeField(const Window& _target, float _height, float _x, float _y, const char* _text, ALIGNMENT_types _aligment, Color _color)
: target(_target),
posX(WINDOW_WIDTH*_x),
aligment(_aligment),
textColor(_color),
font(_target.createFontCopy(FNT_MAIN, _height)),
backRect({_x*WINDOW_WIDTH-(6.5f*bufferSize+2), _y*WINDOW_HEIGHT-_height*0.9f, 13.0f*bufferSize+4, _height*1.8f}) {
    // Setting rects
    textRect = {0, WINDOW_HEIGHT*_y-_height/2-1, 0, 0};
    caretRect = {0, WINDOW_HEIGHT*_y-_height/2-1, 2, _height*1.3f};

    // Copying text to caret
    length = strlen(_text);
    SET_MAX(length, bufferSize);
    memcpy(buffer, _text, length);

    // Creating backplate
    backTexture = target.createTexture(backRect.w, backRect.h);
    target.setRenderTarget(backTexture);
    target.setDrawColor(GREY);
    target.clear();
    target.setDrawColor(WHITE);
    target.drawRect({2, 2, backRect.w-4, backRect.h});
    target.resetRenderTarget();

    // Creating first texture, if there was any text
    if (length) {
        updateTexture();
    }
}

template <unsigned bufferSize>
TypeField<bufferSize>::~TypeField() {
    // Clearing rest texture
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(backTexture);

    // Clearing font
    TTF_CloseFont(font);
}

// Creating new texture
template <unsigned bufferSize>
void TypeField<bufferSize>::updateTexture() {
    // Clearing previous
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }

    // Checking, if string exsist
    if (length) {
        // Creating main surface from all text
        SDL_Surface* mainSurface = TTF_RenderText_Shaded(font, buffer, length, textColor, WHITE);

        // Inversing selected part of text, if need
        if (selectLength) {
            SDL_Surface* inverseSurface = nullptr;
            SDL_Rect inverseRect = {0, 0, 0, 0};

            if (selectLength > 0) {
                if (caret == 0) {
                    inverseRect.x = 0;
                } else {
                    TTF_GetStringSize(font, buffer, caret, &inverseRect.x, nullptr);
                }
                inverseSurface = TTF_RenderText_Shaded(font, buffer + caret, selectLength, textColor, GREY);
            } else {
                if (-selectLength == caret) {
                    inverseRect.x = 0;
                } else {
                    TTF_GetStringSize(font, buffer, caret + selectLength, &inverseRect.x, nullptr);
                }
                inverseSurface = TTF_RenderText_Shaded(font, buffer + caret + selectLength, -selectLength, textColor, GREY);
            }
            // Blitting inverse suface on main
            inverseRect.w = inverseSurface->w;
            inverseRect.h = inverseSurface->h;

            // Filling area with black color
            SDL_BlitSurface(inverseSurface, NULL, mainSurface, &inverseRect);
            SDL_DestroySurface(inverseSurface);
        }
        // Updating texture
        textTexture = target.createTextureAndFree(mainSurface);
        SDL_DestroySurface(mainSurface);

        // Resetting place of text with saving aligment
        textRect.w = textTexture->w;
        textRect.h = textTexture->h;
        textRect.x = SDL_floorf(posX - textRect.w * aligment / 2);
        
        // Update caret place
        if (caret) {
            int caretX = 0;
            TTF_GetStringSize(font, buffer, caret, &caretX, nullptr);
            caretRect.x = textRect.x + caretX - 1;
        } else {
            caretRect.x = textRect.x - 1;
        }
    } else {
        caretRect.x = posX - 1;
    }
}


// Select last letter to create writing symbol
template <unsigned bufferSize>
void TypeField<bufferSize>::select(float _mouseX) {
    // Resetting swapping caret
    showCaret = true;
    selectLength = 0;

    // Getting current mouse position at text
    if (length) {
        TTF_MeasureString(font, buffer, length, _mouseX-textRect.x, NULL, &caret);
    } else {
        caret = 0;
    }

    // Showing caret
    updateTexture();

    // Starting using keyboard
    target.startTextInput();
}

// Write need string to buffer with ability to clear source
template <unsigned bufferSize>
void TypeField<bufferSize>::writeString(const char* _str) {
    if (selected) {
        // Resetting
        pressed = false;
        deleteSelected();

        // Inserting text from clipboard
        size_t clipboardSize = strlen(_str);

        // Checking, if all clipboard can be placed in buffer
        if (clipboardSize > bufferSize - length) {
            clipboardSize = bufferSize - length;
        }

        // Moving part after caret at end
        for (size_t i = length; i > caret; --i) {
            buffer[i + clipboardSize - 1] = buffer[i-1];
        }

        // Coping main clipboard text
        for (size_t i=0; i < clipboardSize; ++i) {
            buffer[caret + i] = _str[i];
        }

        length += clipboardSize;
        caret += clipboardSize;
        updateTexture();
    }
}

// Getting clippboard content
template <unsigned bufferSize>
void TypeField<bufferSize>::writeClipboard() {
    // Getting and writing clipboard to caret
    char* clippboard = SDL_GetClipboardText();
    writeString(clippboard);
    SDL_free(clippboard);
}

// Copying selected text to clipboard
template <unsigned bufferSize>
void TypeField<bufferSize>::copyToClipboard() {
    if (selectLength < 0) {
        memcpy(&clipboardText, buffer + caret + selectLength, abs(selectLength));
    } else {
        memcpy(&clipboardText, buffer + caret, abs(selectLength));
    }
    clipboardText[abs(selectLength)] = '\0';
    SDL_SetClipboardText(clipboardText);
}

template <unsigned bufferSize>
void TypeField<bufferSize>::deleteSelected() {
    if (selectLength) {
        if (selectLength < 0) {
            for (size_t i=caret; i < length; ++i) {
                buffer[i + selectLength] = buffer[i];
            }
            caret += selectLength;
            length += selectLength;
        } else {
            for (size_t i=caret; i < length - selectLength; ++i) {
                buffer[i] = buffer[i + selectLength];
            }
            length -= selectLength;
        }
        selectLength = 0;
    }
}

// Getting press of need KeyCode
template <unsigned bufferSize>
void TypeField<bufferSize>::type(SDL_Keycode _code) {
    // Checking, if box selected
    if (!selected) {
        return;
    }

    // Getting current shft and control state
    SDL_Keymod keyMods = SDL_GetModState();

    // Switching between extra input options
    switch (_code) {
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
            if (caret == length) {
                return;
            }
            selectLength = 1;
        }
        deleteSelected();
        break;

    // Moving caret
    case SDLK_LEFT:
        if (keyMods & SDL_KMOD_SHIFT) {
            if (caret > 0) {
                caret--;
                selectLength++;
            }
        } else {
            if (caret > 0) {
                if (selectLength < 0) {
                    caret += selectLength;
                } else {
                    caret--;
                }
            }
            selectLength = 0;
        }
        break;

    case SDLK_RIGHT:
        if (keyMods & SDL_KMOD_SHIFT) {
            if (caret < length) {
                caret++;
                selectLength--;
            }
        } else {
            if (caret < length) {
                if (selectLength > 0) {
                    caret += selectLength;
                } else {
                    caret++;
                }
            }
            selectLength = 0;
        }
        break;

    // Special keys for faster caret move
    case SDLK_END:
    case SDLK_PAGEDOWN:
        if (keyMods & SDL_KMOD_SHIFT) {
            selectLength += caret - length;
        } else {
            selectLength = 0;
        }
        caret = length;
        break;

    case SDLK_HOME:
    case SDLK_PAGEUP:
        if (keyMods & SDL_KMOD_SHIFT) {
            selectLength += caret;
        } else {
            selectLength = 0;
        }
        caret = 0;
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
            // Selecing all text
            caret = length;
            selectLength = -length;
        }
        break;

    default:
        return;
    }
    // Updating texture after modifiying text
    updateTexture();
}


template <unsigned bufferSize>
void TypeField<bufferSize>::press(const Mouse mouse) {
    if (in(mouse)) {
        pressed = true;
        if (!selected) {
            selected = true;
            select(mouse.getX());
        } else {
            // Stoping entering any letters
            target.stopTextInput();

            // Clearing caret
            showCaret = false;
            selectLength = 0;
            select(mouse.getX());
        }
    } else if (selected) {
        // Resetting selection
        selected = false;
        pressed = false;

        // Stoping entering any letters
        target.stopTextInput();

        // Clearing caret
        showCaret = false;
        selectLength = 0;

        updateTexture();
    }
}

template <unsigned bufferSize>
void TypeField<bufferSize>::unpress() {
    pressed = false;
}

template <unsigned bufferSize>
void TypeField<bufferSize>::update(float _mouseX) {
    if (pressed) {
        size_t measure;
        if (length) {
            TTF_MeasureString(font, buffer, length, _mouseX-textRect.x, NULL, &measure);
        } else {
            measure = 0;
        }
        selectLength += caret - measure;
        SDL_Log("Measured: %d, caret: %d", measure, caret);
        caret = measure;
        updateTexture();
    }
    if (selected && getTime() > needSwapCaret) {
        // Inversing show state
        showCaret ^= true;

        // Update timer
        needSwapCaret = getTime() + 400;
    }
}

template <unsigned bufferSize>
void TypeField<bufferSize>::blit() const {
    // Rendering background picture for better typing
    target.blit(backTexture, backRect);

    // Rendering text
    target.blit(textTexture, textRect);

    // Rendering caret
    if (showCaret) {
        target.setDrawColor({50, 50, 50, 50});
        target.drawRect(caretRect);
    }
}

template <unsigned bufferSize>
bool TypeField<bufferSize>::in(const Mouse mouse) {
    return mouse.in(backRect);
}

// Returning current text
template <unsigned bufferSize>
const char* TypeField<bufferSize>::getString() const {
    return buffer;
}
