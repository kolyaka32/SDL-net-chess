#include "../include.hpp"
#include "../define.hpp"
#include "../data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Button class
ImageButton::ImageButton(float _x, float _y, IMG_names _index) : GUItemplate(){
    // Setting base texture
    texture = data.textures[_index];
    // Setting destination
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _x - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _y - rect.h / 2;
};
