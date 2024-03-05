#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "../dataLoader.hpp"
#include "baseGUI.hpp"

using namespace GUI;

// Slider class
Slider::Slider(const float Y, Uint16 max, const IMG_names lineImage, const IMG_names buttonImage) : GUItemplate(){
    texture = textures[lineImage];
    textureButton = textures[buttonImage];
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    rect.x = SCREEN_WIDTH / 2 - rect.w / 2; 
    rect.y = SCREEN_HEIGHT * Y - rect.h / 2; 
    destButton.y = SCREEN_HEIGHT * Y - destButton.h / 2;
    maxValue = max;
};

void Slider::blit(){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderCopy(renderer, textureButton, NULL, &destButton);
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
