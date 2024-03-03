#include "include.hpp"
#include <string.h>
#include "define.hpp"
#include "values.hpp"
#include "dataLoader.hpp"
#include "baseGUI.hpp"
#include "pause.hpp"

//#define BUFFER_LENGTH 100

using namespace GUI;

// Function of creating font with need height
inline TTF_Font* createFont(textHeight size){
    SDL_RWops* RWopsData = SDL_RWFromMem(fontData.data, fontData.size);
    return TTF_OpenFontRW(RWopsData, 1, size);
};


// Class of static text
staticText::staticText(char* newText, textHeight size, float x, float y, SDL_Color newColor, ALIGNMENT_types newAligment){
    height = size;
    text = newText;
    posX = x;
    posY = y;
    aligment = newAligment;
    color = newColor;
};

void staticText::init(){
    Font = createFont(height);
};

inline void writeNumber(char* buffer, int number, Uint8* pos){
    if(number < 0){
        buffer[*pos++] = '-';
        number = -number;
    }
    Uint8 end = 0;
    int num = number;
    do{
        num /= 10;
        end++;
    } while(num);
    *pos += end;
    do {   
        buffer[--*pos] = '0' + number % 10;
        number /= 10;
    } while (number);
    *pos += end;
};

void staticText::updateText(int number){
    char buffer[BUFFER_SIZE];
    Uint8 start = 0;
    for(Uint8 end = 0; (end != language) && (start < BUFFER_SIZE); ++start){
        if(text[start] == '\n'){
            end++;
        }
    }
    Uint8 d = 0;
    for(int i = start; text[i] && (text[i] != '\n') && (start < BUFFER_SIZE); ++i ){
        switch (text[i])
        {
        case '%':
            writeNumber(buffer, number, &d);
            break;
        
        default:
            buffer[d++] = text[i];
            break;
        }
    }
    buffer[d] = '\0';
    
    SDL_Surface* Surface = TTF_RenderUTF8_Solid(Font, buffer, color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_FreeSurface(Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = SCREEN_WIDTH * posX - (Rect.w * aligment / 2); 
    Rect.y = SCREEN_HEIGHT * posY - Rect.h / 2;
};

void staticText::blit(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

void staticText::free(){
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
};


// Slider class
Slider::Slider(const float Y, Uint16 max, const IMG_names lineImage, const IMG_names buttonImage){
    textureLine = Textures[lineImage];
    textureButton = Textures[buttonImage];
    SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    destLine.x = SCREEN_WIDTH / 2 - destLine.w / 2; 
    destLine.y = SCREEN_HEIGHT * Y - destLine.h / 2; 
    destButton.y = SCREEN_HEIGHT * Y - destButton.h / 2;
    maxValue = max;
};

void Slider::blit(){
    SDL_RenderCopy(app.renderer, textureLine, NULL, &destLine);
    SDL_RenderCopy(app.renderer, textureButton, NULL, &destButton);
};

bool Slider::checkIn(int mouseX, int mouseY){
    return ((mouseX > destLine.x && mouseX < destLine.x + destLine.w) &&
        (mouseY > destLine.y && mouseY < destLine.y + destLine.h));
};

void Slider::setValue(const int mouseX){
    // Getting new position
    destButton.x = mouseX;
    SET_MAX(destButton.x, destLine.x + destLine.w);
    SET_MIN(destButton.x, destLine.x);

    state = (destButton.x - destLine.x) * maxValue / destLine.w;

    destButton.x -= destButton.w / 2;
};

bool Slider::scroll(const Sint32 wheelY, const int mouseX, const int mouseY){
    const static Uint8 deadZone = 1;
    
    if(checkIn(mouseX, mouseY)){
        if(wheelY > deadZone){
            state++;
        }
        else if(wheelY < deadZone){
            state--;
        }
        return true;
    }
    return false;
};


// Button class
Button::Button(const float X, const float Y, const IMG_names newIndex, staticText* top){
    posX = X;
    posY = Y;
    textureIndex = newIndex;
    topText = top;
};

void Button::init(){
    SDL_QueryTexture(Textures[textureIndex], NULL, NULL, &dest.w, &dest.h);
    dest.x = SCREEN_WIDTH * posX - dest.w / 2; 
    dest.y = SCREEN_HEIGHT * posY - dest.h / 2;
};

void Button::blit(){
    SDL_RenderCopy(app.renderer, Textures[textureIndex], NULL, &dest);
    if(topText != nullptr){
        topText->blit();
    }
};

bool Button::in(int x, int y){
    return ((x > dest.x && x < dest.x + dest.w) &&
        (y > dest.y && y < dest.y + dest.h));
};


// Animation class
#if ANI_count
// GIF animation class
Animation::Animation( SDL_Rect destination, ANI_names newType ){
    // Creating animation
    type = newType;
    dest = destination;
    frame = 0; 
    prevTick = 0;
};

void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(app.renderer, Animations[type]->frames[frame]);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    if(SDL_GetTicks64() > prevTick + Animations[type]->delays[0]){
        frame = (frame+1) % Animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

void Animation::clear(){
    SDL_DestroyTexture(texture);
};
#endif


// Bar class
Bar::Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone ){
    // Base bar
    Back_rect = dest;
    Front_rect = dest;
    color = newColor;

    // Icone part
    if(icone){
        IconeTexture = Textures[icone];  // Texture of icone
        IconeRect = dest;
        //SDL_QueryTexture(IconeTexture, NULL, NULL, &IconeRect.w, &IconeRect.h);
        //IconeRect.w = 14;
        //IconeRect.h = 16;

        IconeRect.y -= 2;
        IconeRect.x -= IconeRect.w + 2;
    }
};

void Bar::blit(int width){
    Front_rect.w = width;  // Setting width
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  
    // Drawing back part
    SDL_RenderFillRect(app.renderer, &Back_rect);  
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);  
    // Drawing front part
    SDL_RenderFillRect(app.renderer, &Front_rect);
    // Drawing icone
    if(IconeTexture){
        SDL_RenderCopy(app.renderer, IconeTexture, NULL, &IconeRect);
    }
};


// Type box class
typeBox::typeBox(textHeight size, float posX, float posY, const char* startText, ALIGNMENT_types newAligment, SDL_Color newColor){
    Font = createFont(size);
    dest.x = SCREEN_WIDTH * posX;
    dest.y = SCREEN_HEIGHT * posY - size / 2;
    dest.w = dest.h = 0;

    aligment = newAligment;
    color = newColor;

    strcpy(buffer, startText);
    length = caret = strlen(buffer);
    if(caret){
        updateTexture();
    }

    // Creating background picture for typing
    SDL_QueryTexture(Textures[IMG_MENU_TYPE_BOX], NULL, NULL, &backRect.w, &backRect.h);
    backRect.x = SCREEN_WIDTH * posX - backRect.w/2;
    backRect.y = SCREEN_HEIGHT * posY - backRect.h/2 - 2;
}

typeBox::~typeBox(){
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}

// Creating new texture
void typeBox::updateTexture(){
    SDL_Surface* Surface = TTF_RenderUTF8_Solid(Font, buffer, color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
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
    SDL_RenderCopy(app.renderer, Textures[IMG_MENU_TYPE_BOX], NULL, &backRect);

    // Rendering text
    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);
};
