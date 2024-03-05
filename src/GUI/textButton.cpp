#include "../include.hpp"
#include "../define.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Button class
TextButton::TextButton(float _x, float _y, staticText &_text) : GUItemplate(), topText (_text){
    // Setting base texture
    texture = textures[IMG_MENU_BUTTON];
    
    // Setting destination
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _x - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _y - rect.h / 2;
};

void TextButton::blit(){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    topText.blit();
};
