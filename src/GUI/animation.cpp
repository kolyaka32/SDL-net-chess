#include "../include.hpp"
#include "../define.hpp"
#include "../data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

#if ANI_count
// GIF animation class
//
GIFAnimation::GIFAnimation( SDL_Rect _rect, ANI_names _type ){
    // Creating animation
    type = _type;
    rect = _rect;
    frame = 0; 
    prevTick = 0;
};

//
GIFAnimation::~GIFAnimation(){
    SDL_DestroyTexture(texture);
}

//
void GIFAnimation::blit(){
    texture = SDL_CreateTextureFromSurface(renderer, animations[type]->frames[frame]);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    if(SDL_GetTicks64() > prevTick + animations[type]->delays[frame]){
        frame = (frame + 1) % animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

#endif