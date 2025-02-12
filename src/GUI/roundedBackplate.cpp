/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;

// Class of backplates (smoothed rects)
Backplate::Backplate(Window& _target, float _centerX, float _centerY, float _width, float _height,
    float _rad, float _bor, SDL_Color _frontColor, const SDL_Color _backColor)
: frontColor(_frontColor), backColor(_backColor), rad(_rad), bor(_bor) {
    updatePlate(_target, {SCREEN_WIDTH * (_centerX - _width/2), SCREEN_HEIGHT * (_centerY - _height/2),
        SCREEN_WIDTH * _width, SCREEN_HEIGHT * _height});
}

Backplate::Backplate(Window& _target, float _rad, float _bor, const SDL_Color _frontColor, const SDL_Color _backColor)
: frontColor(_frontColor), backColor(_backColor), rad(_rad), bor(_bor) {
    rect = {0, 0, 0, 0};
}

Backplate::~Backplate() {
    SDL_DestroyTexture(texture);
}

void Backplate::updatePlate(Window& _target, const SDL_FRect& _rect) {
    // Checking, if need clear previous texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Creating new texture for drawing
    texture = _target.createTexture(_rect.w, _rect.h);
    rect = _rect;

    // Setting render target to this texture
    //SDL_SetRenderTarget(data.renderer, texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Drawing back part
    _target.setDrawColor(backColor);
    _target.clear();

    // Drawing front part
    _target.setDrawColor(frontColor);
    _target.drawRect({bor, bor, rect.w - bor * 2, rect.h - bor * 2});

    // Clearing front edges
    _target.setDrawColor(backColor);
    for (float y=0; y <= rad+bor; ++y) {
        for (float x=0; x <= rad+bor; ++x) {
            if (sqr(y)+sqr(x) >= sqr(rad-bor)) {
                _target.drawPoint(rad-x, rad-y);
                _target.drawPoint(rect.w-rad+x, rad-y);
                _target.drawPoint(rad-x, rect.h-rad+y);
                _target.drawPoint(rect.w-rad+x, rect.h-rad+y);
            }
        }
    }

    // Clearing back edges
    _target.setDrawColor(WHITE);
    for (float y=0; y <= rad; ++y) {
        for (float x=0; x <= rad; ++x) {
            if (sqr(y)+sqr(x) >= sqr(rad)) {
                _target.drawPoint(rad-x, rad-y);
                _target.drawPoint(rect.w-rad+x, rad-y);
                _target.drawPoint(rad-x, rect.h-rad+y);
                _target.drawPoint(rect.w-rad+x, rect.h-rad+y);
            }
        }
    }

    // Setting texture for using
    SDL_UnlockTexture(texture);

    // Resetting render target
    _target.resetRenderTarget();
}
