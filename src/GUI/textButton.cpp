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
    //topText = _text;
    // Setting destination
    SDL_QueryTexture(process.graphics[IMG_MENU_BUTTON], NULL, NULL, &dest.w, &dest.h);
    dest.x = SCREEN_WIDTH * _x - dest.w / 2;
    dest.y = SCREEN_HEIGHT * _y - dest.h / 2;
};

void TextButton::blit(){
    SDL_RenderCopy(process.app.renderer, process.graphics[IMG_MENU_BUTTON], NULL, &dest);
    topText.blit();
};

bool TextButton::in(int x, int y){
    return ((x > dest.x && x < dest.x + dest.w) &&
        (y > dest.y && y < dest.y + dest.h));
};
