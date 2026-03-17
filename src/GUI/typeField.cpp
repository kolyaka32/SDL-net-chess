/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)

#include <cstdlib>
#include <algorithm>


// Type field class
template <unsigned bufferSize>
GUI::TypeField<bufferSize>::TypeField(const Window& _window, float _X, float _Y, const char* _startText,
    float _height, Aligment _aligment, Color _textColor, Color _backColor)
: TextureTemplate(_window),
posX(window.getWidth()*_X),
aligment(_aligment),
textColor(_textColor),
backColor(_backColor),
font(window.createFontCopy(Fonts::Main, _height)) {
    // Setting rects
    rect = {0, window.getHeight()*_Y-_height/2, 0, 0};
    caretRect = {0, window.getHeight()*_Y-_height/2, 2, 0};
    inversedRectDest.y = window.getHeight()*_Y-_height/2;
    inversedRectSrc.y = 0;

    // Copying text to caret
    length = strlen(_startText);
    setMax(length, (size_t)bufferSize);
    memcpy(buffer, _startText, length);

    // Creating first texture, if there was any text
    if (length) {
        updateTexture();
    } else {
        // Create empty texture
        texture = window.createTexture(font, "1", textColor);
        inverseTexture = window.createTexture(font, "1", textColor);
    }
    // Setting height of text
    inversedRectDest.h = inversedRectSrc.h = caretRect.h = rect.h = texture->h;
}

template <unsigned bufferSize>
GUI::TypeField<bufferSize>::TypeField(TypeField&& _object) noexcept
: TextureTemplate(std::move(_object)),
posX(_object.posX),
aligment(_object.aligment),
textColor(_object.textColor),
backColor(_object.backColor),
font(_object.font),
length(_object.length),
caret(_object.caret),
needSwapCaret(_object.needSwapCaret),
selectLength(_object.selectLength),
showCaret(_object.showCaret),
caretRect(_object.caretRect),
inversedRectDest(_object.inversedRectDest),
inversedRectSrc(_object.inversedRectSrc),
inverseTexture(_object.inverseTexture),
pressed(_object.pressed),
selected(_object.selected) {
    // Copying previous text
    memcpy(buffer, _object.buffer, bufferSize+1);
}

template <unsigned bufferSize>
GUI::TypeField<bufferSize>::~TypeField() noexcept {
    // Check, if not moved
    if (texture) {
        // Clearing rest texture
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(inverseTexture);
        
        // Clearing font
        TTF_CloseFont(font);
    }
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::updateTexture() {
    // Checking, if string exsist
    if (length) {
        // Clearing previous
        if (texture) {
            SDL_DestroyTexture(texture);
            SDL_DestroyTexture(inverseTexture);
        }

        // Creating main text texture
        SDL_Surface* mainSurface = TTF_RenderText_Shaded(font, buffer, length, textColor, backColor);
        texture = window.createTextureAndFree(mainSurface);

        // Create inversed text texture
        SDL_Surface* inversedSurface = TTF_RenderText_Shaded(font, buffer, length, backColor, textColor);
        inverseTexture = window.createTextureAndFree(inversedSurface);

        // Resetting place of text with saving aligment
        rect.w = texture->w;
        rect.x = SDL_floorf(posX - rect.w * (unsigned)aligment / 2);
        updateSelected();
    } else {
        caretRect.x = posX - 1;
    }
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::updateSelected() {
    // Update caret place
    if (caret) {
        int caretX = 0;
        TTF_GetStringSize(font, buffer, caret, &caretX, nullptr);
        caretRect.x = rect.x + caretX - 1;
    } else {
        caretRect.x = rect.x - 1;
    }

    // Inversing selected part of text, if need
    if (selectLength) {
        // Getting start position and length of selected part
        int startPosition, length;
        if (selectLength > 0) {
            if (caret == 0) {
                startPosition = 0;
            } else {
                TTF_GetStringSize(font, buffer, caret, &startPosition, nullptr);
            }
            TTF_GetStringSize(font, buffer+caret, selectLength, &length, nullptr);
        } else {
            if (-selectLength == caret) {
                startPosition = 0;
            } else {
                TTF_GetStringSize(font, buffer, caret + selectLength, &startPosition, nullptr);
            }
            TTF_GetStringSize(font, buffer+caret+selectLength, -selectLength, &length, nullptr);
        }
        inversedRectSrc.x = startPosition;
        inversedRectDest.x = inversedRectSrc.x + rect.x;
        inversedRectDest.w = inversedRectSrc.w = length;
    }
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::writeString(const char* _str) {
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

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::writeClipboard() {
    // Getting and writing clipboard to caret
    char* clippboard = SDL_GetClipboardText();
    writeString(clippboard);
    SDL_free(clippboard);
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::copyToClipboard() {
    if (selectLength) {
        // Static memory for write clipbpard
        static char clipboardText[100];
        if (selectLength < 0) {
            memcpy(clipboardText, buffer + caret + selectLength, min(-selectLength, (int)sizeof(clipboardText)));
        } else {
            memcpy(clipboardText, buffer + caret, min(selectLength, (int)sizeof(clipboardText)));
        }
        clipboardText[abs(selectLength)] = '\0';
        SDL_SetClipboardText(clipboardText);
    }
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::deleteSelected() {
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

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::type(SDL_Keycode _code) {
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
        updateSelected();
        return;

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
        updateSelected();
        return;

    // Special keys for faster caret move
    case SDLK_END:
    case SDLK_PAGEDOWN:
        if (keyMods & SDL_KMOD_SHIFT) {
            selectLength += caret - length;
        } else {
            selectLength = 0;
        }
        caret = length;
        updateSelected();
        return;

    case SDLK_HOME:
    case SDLK_PAGEUP:
        if (keyMods & SDL_KMOD_SHIFT) {
            selectLength += caret;
        } else {
            selectLength = 0;
        }
        caret = 0;
        updateSelected();
        return;

    // Clipboard
    case SDLK_PASTE:
        writeClipboard();
        break;

    case SDLK_COPY:
        copyToClipboard();
        break;

    case SDLK_CUT:
        copyToClipboard();
        deleteSelected();
        break;

    case SDLK_V:
        if (keyMods & SDL_KMOD_CTRL) {
            writeClipboard();
        } else {
            return;
        }
        break;

    case SDLK_C:
        if (keyMods & SDL_KMOD_CTRL) {
            copyToClipboard();
        } else {
            return;
        }
        break;

    case SDLK_X:
        if (keyMods & SDL_KMOD_CTRL) {
            copyToClipboard();
            deleteSelected();
        } else {
            return;
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
bool GUI::TypeField<bufferSize>::click(const Mouse _mouse) {
    if (in(_mouse)) {
        // Resetting values
        pressed = true;
        showCaret = true;
        selectLength = 0;
        if (!selected) {
            // Starting using keyboard
            window.startTextInput();
            selected = true;
        }

        // Getting current mouse position at text
        if (length) {
            TTF_MeasureString(font, buffer, length, _mouse.getX()-rect.x, NULL, &caret);
        } else {
            caret = 0;
        }
        // Showing caret
        updateSelected();
        return false;
    } else if (selected) {
        // Resetting selection
        selected = false;
        pressed = false;

        // Stoping entering any letters
        window.stopTextInput();

        // Clearing caret
        showCaret = false;
        selectLength = 0;

        updateSelected();

        // Return, that finish text input
        return true;
    }
    return false;
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::unclick() {
    pressed = false;
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::update(float _mouseX) {
    if (pressed) {
        size_t measure;
        if (length) {
            TTF_MeasureString(font, buffer, length, _mouseX-rect.x, NULL, &measure);
        } else {
            measure = 0;
        }
        selectLength += caret - measure;
        caret = measure;
        updateSelected();
    }
    if (selected && getTime() > needSwapCaret) {
        // Inversing show state
        showCaret ^= true;

        // Update timer
        needSwapCaret = getTime() + 400;
    }
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::blit() const {
    // Rendering main text
    if (length) {
        window.blit(texture, rect);
    }

    // Rendering selection text (as reversed)
    if (selectLength) {
        window.blit(inverseTexture, &inversedRectDest, &inversedRectSrc);
    }

    // Rendering caret
    if (showCaret) {
        window.setDrawColor({50, 50, 50, 50});
        window.drawRect(caretRect);
    }
}

template <unsigned bufferSize>
const char* GUI::TypeField<bufferSize>::getString() {
    buffer[length] = '\0';
    return buffer;
}

template <unsigned bufferSize>
void GUI::TypeField<bufferSize>::setString(const char* _newString) {
    length = min(strlen(_newString), (size_t)bufferSize);
    memcpy(buffer, _newString, length);

    // Resetting
    selected = false;
    pressed = false;

    // Stoping entering any letters
    window.stopTextInput();

    // Clearing caret
    showCaret = false;
    selectLength = 0;

    updateTexture();
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
