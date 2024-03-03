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
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = SCREEN_WIDTH * _x - dest.w / 2;
    dest.y = SCREEN_HEIGHT * _y - dest.h / 2;
};

void ImageButton::blit(){
    SDL_RenderCopy(process.renderer, texture, NULL, &dest);
};

bool ImageButton::in(int x, int y){
    return ((x > dest.x && x < dest.x + dest.w) &&
        (y > dest.y && y < dest.y + dest.h));
};
