#include "../include.hpp"
#include "../define.hpp"
#include "../process.hpp"
#include "../values.hpp"
#include "../dataLoader.hpp"
#include "baseGUI.hpp"
#include "../pause.hpp"

using namespace GUI;

// Class of static text
staticText::staticText(char* _text, textHeight _height, float _x, float _y, SDL_Color _color, ALIGNMENT_types _aligment){
    //height = _height;
    font = process.createFont(_height);
    text = _text;
    //posX = _x;
    //posY = _y;
    aligment = _aligment;
    color = _color;
};

/*void staticText::init(){
    Font = process.font.createFont(height);
};*/

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
    Texture = SDL_CreateTextureFromSurface(process.app.renderer, Surface);
    SDL_FreeSurface(Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = SCREEN_WIDTH * posX - (Rect.w * aligment / 2); 
    Rect.y = SCREEN_HEIGHT * posY - Rect.h / 2;
};

void staticText::blit(){
    SDL_RenderCopy(process.app.renderer, Texture, NULL, &Rect);
};

void staticText::free(){
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
};
