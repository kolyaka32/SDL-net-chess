#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "../dataLoader.hpp"
#include "baseGUI.hpp"
#include "../process.hpp"

using namespace GUI;

// Slider class
Slider::Slider(const float Y, Uint16 max, const IMG_names lineImage, const IMG_names buttonImage){
    textureLine = process.graphics[lineImage];
    textureButton = process.graphics[buttonImage];
    SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    destLine.x = SCREEN_WIDTH / 2 - destLine.w / 2; 
    destLine.y = SCREEN_HEIGHT * Y - destLine.h / 2; 
    destButton.y = SCREEN_HEIGHT * Y - destButton.h / 2;
    maxValue = max;
};

void Slider::blit(){
    SDL_RenderCopy(process.app.renderer, textureLine, NULL, &destLine);
    SDL_RenderCopy(process.app.renderer, textureButton, NULL, &destButton);
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
