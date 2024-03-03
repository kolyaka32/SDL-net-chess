#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "baseGUI.hpp"

using namespace GUI;

#if ANI_count
// GIF animation class
Animation::Animation( SDL_Rect destination, ANI_names newType ){
    // Creating animation
    type = newType;
    dest = destination;
    frame = 0; 
    prevTick = 0;
};

void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(process.app.renderer, Animations[type]->frames[frame]);
    SDL_RenderCopy(process.app.renderer, texture, NULL, &dest);
    if(SDL_GetTicks64() > prevTick + Animations[type]->delays[0]){
        frame = (frame+1) % Animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

void Animation::clear(){
    SDL_DestroyTexture(texture);
};
#endif