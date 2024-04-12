#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Button class
TextButton::TextButton(StaticText &_text) : Backplate({_text.rect.x-10, _text.rect.y-1, _text.rect.w+20, _text.rect.h+4}, _text.rect.h/2, 3), topText (_text){
    
};

//
void TextButton::blit() const{
    SDL_RenderCopy(data.renderer, texture, NULL, &rect);
    topText.blit();
};
