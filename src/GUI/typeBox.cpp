#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "../dataLoader.hpp"
#include "../GUI/baseGUI.hpp"
#include "../pause.hpp"
#include "../process.hpp"

using namespace GUI;


// Type box class
typeBox::typeBox(textHeight _height, float _x, float _y, const char* _text, ALIGNMENT_types _aligment, SDL_Color _color){
    Font = process.font.createFont(_height);
    dest.x = SCREEN_WIDTH * _x;
    dest.y = SCREEN_HEIGHT * _y - _height / 2;
    dest.w = dest.h = 0;

    aligment = _aligment;
    color = _color;

    strcpy(buffer, _text);
    length = caret = strlen(buffer);
    if(caret){
        updateTexture();
    }

    // Creating background picture for typing
    SDL_QueryTexture(process.graphics[IMG_MENU_TYPE_BOX], NULL, NULL, &backRect.w, &backRect.h);
    backRect.x = SCREEN_WIDTH * _x - backRect.w/2;
    backRect.y = SCREEN_HEIGHT * _y - backRect.h/2 - 2;
}

typeBox::~typeBox(){
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}

// Creating new texture
void typeBox::updateTexture(){
    SDL_Surface* Surface = TTF_RenderUTF8_Solid(Font, buffer, color);
    Texture = SDL_CreateTextureFromSurface(process.app.renderer, Surface);
    SDL_FreeSurface(Surface);
    dest.x += dest.w * aligment / 2;
    SDL_QueryTexture(Texture, NULL, NULL, &dest.w, &dest.h);
    dest.x -= dest.w * aligment / 2;
}

void typeBox::writeString(char* str, bool freeData){
    // Inserting text from clipboard
    Uint8 clipboardSize = strlen(str);

    // Checking, if all clipboard can be placed in buffer
    if(clipboardSize > bufferSize - length){
        clipboardSize = bufferSize - length;
    }

    // Moving part after caret at end
    for(Sint8 i = length; i >= caret; --i){
        buffer[i + clipboardSize] = buffer[i];
    }

    // Coping main clipboard text
    for(Uint8 i=0; i < clipboardSize; ++i){
        buffer[caret + i] = str[i];
    }

    length += clipboardSize;
    caret += clipboardSize;

    updateTexture();

    if(freeData){
        SDL_free(str);
    }
};

void typeBox::press(SDL_Keycode code){
    static SDL_Keycode preCode;
    switch (code)
    {
    case SDLK_BACKSPACE:
        // Coping after caret
        if(caret > 0){
            for(Uint8 t = --caret; t <= length; t++){
                buffer[t] = buffer[t+1];
            }
            length--;
        }
        break;

    case SDLK_DELETE:
        // Coping after caret
        if(caret < length){
            for(Uint8 t = caret + 1; t <= length; t++){
                buffer[t] = buffer[t+1];
            }
            length--;
        }
        break;
    
    case SDLK_LEFT:
        if(caret > 0){
            std::swap(buffer[caret--], buffer[caret - 1]);
        }
        break;
    
    case SDLK_RIGHT:
        if(caret+1 < length){
            std::swap(buffer[caret++], buffer[caret + 1]);
        }
        break;
    
    // Control-v mode
    case SDLK_PASTE:
        // Inserting text from clipboard
        writeString(SDL_GetClipboardText(), true);
        break;
        
    case SDLK_v:
        if(preCode == SDLK_LCTRL){
            writeString(SDL_GetClipboardText(), true);
        }
        break;

    case SDLK_LCTRL:
        if(preCode == SDLK_v){
            writeString(SDL_GetClipboardText(), true);
        }
        break;
    };
    updateTexture();
    preCode = code;
};

void typeBox::select(){
    buffer[length] = '|';
    caret = length++;
    buffer[length] = '\0';
    updateTexture();

    // Starting using keyboard
    SDL_StartTextInput();
};

void typeBox::removeSelect(){
    // Stoping entering any letters
    SDL_StopTextInput();

    for(Uint8 t = caret; t <= length; t++){
        buffer[t] = buffer[t+1];
    }
    length--;
    updateTexture();
};

void typeBox::updateCaret(){
    static char b = ' ';
    std::swap(buffer[caret], b);
    updateTexture();
};

bool typeBox::in(int x, int y){
    return ((x > backRect.x && x < backRect.x + backRect.w) &&
        (y > backRect.y && y < backRect.y + backRect.h));
};

void typeBox::blit(){
    // Rendering background picture for better typing
    SDL_RenderCopy(process.app.renderer, process.graphics[IMG_MENU_TYPE_BOX], NULL, &backRect);

    // Rendering text
    SDL_RenderCopy(process.app.renderer, Texture, NULL, &dest);
};
