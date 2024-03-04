#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "baseGUI.hpp"
#include "../process.hpp"

using namespace GUI;


// Button class
TextButton::TextButton(float _x, float _y, staticText &_text) : topText (_text){
    posX = _x;
    posY = _y;
    // Setting destination
    SDL_QueryTexture(process.textures[IMG_MENU_BUTTON], NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDTH * _x - rect.w / 2;
    rect.y = SCREEN_HEIGHT * _y - rect.h / 2;
};

void TextButton::blit(){
    SDL_RenderCopy(renderer, process.textures[IMG_MENU_BUTTON], NULL, &rect);
    topText.blit();
};
