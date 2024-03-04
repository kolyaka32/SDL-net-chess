#include "../include.hpp"
#include "baseGUI.hpp"

using namespace GUI;

GUItemplate::GUItemplate(){
    texture = nullptr;
};

GUItemplate::~GUItemplate(){

};

void GUItemplate::blit(){
    SDL_RenderCopy(renderer, texture, NULL, &rect);
};

bool GUItemplate::in(int mouseX, int mouseY){
    return ((mouseX > rect.x && mouseX < rect.x + rect.w) &&
        (mouseY > rect.y && mouseY < rect.y + rect.h));
};
