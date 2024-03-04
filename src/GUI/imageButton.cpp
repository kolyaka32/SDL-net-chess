#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "baseGUI.hpp"
#include "../process.hpp"

using namespace GUI;


// Button class
ImageButton::ImageButton(float _x, float _y, IMG_names _index){
    posX = _x;
    posY = _y;
    texture = process.textures[_index];
    // Setting destination
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _x - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _y - rect.h / 2;
};

void ImageButton::blit(){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
};
