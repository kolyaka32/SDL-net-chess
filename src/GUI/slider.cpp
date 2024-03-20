#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

// Slider class
Slider::Slider(float _X, float _Y, Uint16 _startPos, IMG_names _lineImage, IMG_names _buttonImage, Uint16 _max) : GUItemplate(){
    texture = data.textures[_lineImage];
    textureButton = data.textures[_buttonImage];
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    rect.x = SCREEN_WIDTH * _X - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _Y - rect.h / 2;
    destButton.y = SCREEN_HEIGHT * _Y - destButton.h / 2;
    maxValue = _max;
    state = _startPos;
};

void Slider::blit(){
    SDL_RenderCopy(data.renderer, texture, NULL, &rect);
    SDL_RenderCopy(data.renderer, textureButton, NULL, &destButton);
};

void Slider::setValue(const int mouseX){
    // Getting new position
    destButton.x = mouseX;
    SET_MAX(destButton.x, rect.x + rect.w);
    SET_MIN(destButton.x, rect.x);

    state = (destButton.x - rect.x) * maxValue / rect.w;

    destButton.x -= destButton.w / 2;
};

bool Slider::scroll(const Sint32 wheelY, const int mouseX, const int mouseY){
    const static Uint8 deadZone = 1;
    
    if(in(mouseX, mouseY)){
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
