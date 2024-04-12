#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

//
Backplate::Backplate(const SDL_Rect _rect, const Uint8 _rad, const Uint8 _bor, const SDL_Color _frontColor, const SDL_Color _backColor){
    // Creating texture for all work
    texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, _rect.w, _rect.h);
    rect = _rect;

    // Setting render target to this texture
    SDL_SetRenderTarget(data.renderer, texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Drawing back part
    data.setColor(_backColor);
    SDL_RenderClear(data.renderer);

    // Drawing front part
    data.setColor(_frontColor);
    SDL_Rect dest = {_bor, _bor, rect.w - _bor * 2, rect.h - _bor * 2};
    SDL_RenderFillRect(data.renderer, &dest);

    // Clearing front edges
    data.setColor(_backColor);
    for(Uint8 y=0; y <= _rad+_bor; ++y){
        for(Uint8 x=0; x <= _rad+_bor; ++x){
            if(sqr(y)+sqr(x) >= sqr(_rad-_bor)){
                SDL_RenderDrawPoint(data.renderer, _rad-x, _rad-y);
                SDL_RenderDrawPoint(data.renderer, rect.w-_rad+x, _rad-y);
                SDL_RenderDrawPoint(data.renderer, _rad-x, rect.h-_rad+y);
                SDL_RenderDrawPoint(data.renderer, rect.w-_rad+x, rect.h-_rad+y);
            }
        }
    }

    // Clearing back edges
    SDL_SetRenderDrawColor(data.renderer, 255, 255, 255, 0);
    for(Uint8 y=0; y <= _rad; ++y){
        for(Uint8 x=0; x <= _rad; ++x){
            if(sqr(y)+sqr(x) >= sqr(_rad)){
                SDL_RenderDrawPoint(data.renderer, _rad-x, _rad-y);
                SDL_RenderDrawPoint(data.renderer, rect.w-_rad+x, _rad-y);
                SDL_RenderDrawPoint(data.renderer, _rad-x, rect.h-_rad+y);
                SDL_RenderDrawPoint(data.renderer, rect.w-_rad+x, rect.h-_rad+y);
            }
        }
    }

    // Setting texture for using
    SDL_UnlockTexture(texture);

    // Resetting render target
    SDL_SetRenderTarget(data.renderer, nullptr);
};

Backplate::~Backplate(){
    SDL_DestroyTexture(texture);
};
