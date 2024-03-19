#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

// Class of static text
staticText::staticText(const char* _text, textHeight _height, float _x, float _y, SDL_Color _color, ALIGNMENT_types _aligment) : GUItemplate(), text (_text){
    font = data.createFont(_height);
    posX = _x;
    posY = _y;
    aligment = _aligment;
    color = _color;
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
    for(Uint8 end = 0; (end != data.language) && (start < BUFFER_SIZE); ++start){
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
    
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, buffer, color);
    texture = SDL_CreateTextureFromSurface(data.renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * posX - (rect.w * aligment / 2); 
    rect.y = SCREEN_HEIGHT * posY - rect.h / 2;
};

staticText::~staticText(){
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}