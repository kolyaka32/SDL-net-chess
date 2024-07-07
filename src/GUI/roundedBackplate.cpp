/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

// Class of backplates (smoothed rects)
Backplate::Backplate(float _centerX, float _centerY, float _width, float _height,
    Uint8 _rad, Uint8 _bor, SDL_Color _frontColor, SDL_Color _backColor)
: frontColor(_frontColor), backColor(_backColor), rad(_rad), bor(_bor) {
    updatePlate({int(SCREEN_WIDTH * (_centerX - _width/2)), int(SCREEN_HEIGHT * (_centerY - _height/2)),
        int(SCREEN_WIDTH * _width), int(SCREEN_HEIGHT * _height)});
}

Backplate::Backplate(const Uint8 _rad, const Uint8 _bor, const SDL_Color _frontColor, const SDL_Color _backColor)
: frontColor(_frontColor), backColor(_backColor), rad(_rad), bor(_bor) {
    rect = {0, 0, 0, 0};
}

Backplate::~Backplate() {
    SDL_DestroyTexture(texture);
}

void Backplate::updatePlate(const SDL_Rect _rect) {
    // Checking, if need clear previous texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Creating new texture for drawing
    texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, _rect.w, _rect.h);
    rect = _rect;

    // Setting render target to this texture
    SDL_SetRenderTarget(data.renderer, texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Drawing back part
    data.setColor(backColor);
    SDL_RenderClear(data.renderer);

    // Drawing front part
    data.setColor(frontColor);
    SDL_Rect dest = {bor, bor, rect.w - bor * 2, rect.h - bor * 2};
    SDL_RenderFillRect(data.renderer, &dest);

    // Clearing front edges
    data.setColor(backColor);
    for (Uint8 y=0; y <= rad+bor; ++y) {
        for (Uint8 x=0; x <= rad+bor; ++x) {
            if (sqr(y)+sqr(x) >= sqr(rad-bor)) {
                SDL_RenderDrawPoint(data.renderer, rad-x, rad-y);
                SDL_RenderDrawPoint(data.renderer, rect.w-rad+x, rad-y);
                SDL_RenderDrawPoint(data.renderer, rad-x, rect.h-rad+y);
                SDL_RenderDrawPoint(data.renderer, rect.w-rad+x, rect.h-rad+y);
            }
        }
    }

    // Clearing back edges
    SDL_SetRenderDrawColor(data.renderer, 255, 255, 255, 0);
    for (Uint8 y=0; y <= rad; ++y) {
        for (Uint8 x=0; x <= rad; ++x) {
            if (sqr(y)+sqr(x) >= sqr(rad)) {
                SDL_RenderDrawPoint(data.renderer, rad-x, rad-y);
                SDL_RenderDrawPoint(data.renderer, rect.w-rad+x, rad-y);
                SDL_RenderDrawPoint(data.renderer, rad-x, rect.h-rad+y);
                SDL_RenderDrawPoint(data.renderer, rect.w-rad+x, rect.h-rad+y);
            }
        }
    }

    // Setting texture for using
    SDL_UnlockTexture(texture);

    // Resetting render target
    SDL_SetRenderTarget(data.renderer, nullptr);
}
