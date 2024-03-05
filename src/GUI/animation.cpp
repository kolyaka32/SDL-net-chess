#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "baseGUI.hpp"

using namespace GUI;

#if ANI_count
// GIF animation class
Animation::Animation( SDL_Rect _rect, ANI_names _type ){
    // Creating animation
    type = _type;
    rest = _rect;
    frame = 0; 
    prevTick = 0;
};

void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(renderer, animations[type]->frames[frame]);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    if(SDL_GetTicks64() > prevTick + Animations[type]->delays[0]){
        frame = (frame+1) % Animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

void Animation::clear(){
    SDL_DestroyTexture(texture);
};
#endif