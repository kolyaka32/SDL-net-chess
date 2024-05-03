#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Type box class
typeBox::typeBox(textHeight _height, float _x, float _y, const char* _text, ALIGNMENT_types _aligment, SDL_Color _color)
 : color(_color), aligment(_aligment){
    font = data.createFont(_height);
    rect.x = SCREEN_WIDTH * _x;
    rect.y = SCREEN_HEIGHT * _y - _height / 2;
    rect.w = rect.h = 0;

    strcpy(buffer, _text);
    length = caret = strlen(buffer);
    if(caret){
        updateTexture();
    }

    // Creating background picture for typing
    SDL_QueryTexture(data.textures[IMG_GUI_TYPE_BOX], NULL, NULL, &backRect.w, &backRect.h);
    backRect.x = SCREEN_WIDTH * _x - backRect.w / 2;
    backRect.y = SCREEN_HEIGHT * _y - backRect.h / 2 + 2;
}

//
typeBox::~typeBox(){
    SDL_DestroyTexture(texture);
}

// Creating new texture
void typeBox::updateTexture(){
    // Creating surface from text
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, buffer, color);
    // Updating texture
    texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    SDL_FreeSurface(surface);

    // Resetting place of text with saving aligment
    rect.x += rect.w * aligment / 2;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x -= rect.w * aligment / 2;
}

//
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

// 
void typeBox::press(SDL_Keycode code){
    static SDL_Keycode preCode;

    // Switching between extra input options
    switch (code)
    {
    // Functions for deleting text
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
    
    // Moving caret
    case SDLK_LEFT:
        if(caret > 0){
            std::swap(buffer[caret--], buffer[caret - 1]);
        }
        break;
    
    case SDLK_RIGHT:
        if(caret + 1 < length){
            std::swap(buffer[caret++], buffer[caret + 1]);
        }
        break;
    
    case SDLK_END:
    case SDLK_PAGEDOWN:
        std::swap(buffer[caret], buffer[length]);
        caret = length;
        break;

    case SDLK_HOME:
    case SDLK_PAGEUP:
        std::swap(buffer[caret], buffer[0]);
        caret = 0;
        break;
    
    // Inserting text from clipboard
    case SDLK_PASTE:
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

//
void typeBox::select(){
    buffer[length] = '|';
    caret = length++;
    buffer[length] = '\0';
    updateTexture();

    // Starting using keyboard
    SDL_StartTextInput();
};

//
void typeBox::removeSelect(){
    // Stoping entering any letters
    SDL_StopTextInput();

    for(Uint8 t = caret; t <= length; t++){
        buffer[t] = buffer[t+1];
    }
    length--;
    updateTexture();
};

//
void typeBox::updateCaret(){
    static char b = ' ';
    std::swap(buffer[caret], b);
    updateTexture();
};

//
void typeBox::blit() const{
    // Rendering background picture for better typing
    SDL_RenderCopy(data.renderer, data.textures[IMG_GUI_TYPE_BOX], NULL, &backRect);

    // Rendering text
    SDL_RenderCopy(data.renderer, texture, NULL, &rect);
};
