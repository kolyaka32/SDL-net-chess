#include "../include.hpp"
#include "baseGUI.hpp"

using namespace GUI;

void GUItemplate::blit(){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
};

bool GUItemplate::in(const int mouseX, const int mouseY){
    return ((mouseX > rect.x && mouseX < rect.x + rect.w) &&
        (mouseY > rect.y && mouseY < rect.y + rect.h));
};
