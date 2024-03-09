#include "../include.hpp"
#include "../data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

GUItemplate::GUItemplate(){
    texture = nullptr;
}

void GUItemplate::blit(){
    SDL_RenderCopy(data.renderer, texture, NULL, &rect);
};

bool GUItemplate::in(const int mouseX, const int mouseY){
    return ((mouseX > rect.x && mouseX < rect.x + rect.w) &&
        (mouseY > rect.y && mouseY < rect.y + rect.h));
};
