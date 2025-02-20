/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;

// Class of backplates (smoothed rects)
Backplate::Backplate(const Window& _target, float _centerX, float _centerY, float _width, float _height,
    float _rad, float _bor, SDL_Color _frontColor, SDL_Color _backColor)
: Backplate(_target, {SDL_roundf(SCREEN_WIDTH * (_centerX - _width/2)), SDL_roundf(SCREEN_HEIGHT * (_centerY - _height/2)),
    SDL_roundf(SCREEN_WIDTH * _width), SDL_roundf(SCREEN_HEIGHT * _height)}, _rad, _bor, _frontColor, _backColor) {}

// Creating backplate depend from rect, where it should be
Backplate::Backplate(const Window& _target, const SDL_FRect& _rect, float _rad, float _bor, SDL_Color _frontColor, SDL_Color _backColor) {
    // Creating new texture for drawing
    texture = _target.createTexture(_rect.w, _rect.h);
    rect = _rect;

    // Setting render target to this texture
    _target.setRenderTarget(texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Drawing back part
    _target.setDrawColor(_backColor);
    _target.clear();

    // Drawing front part
    _target.setDrawColor(_frontColor);
    _target.drawRect({_bor, _bor, rect.w-_bor * 2, rect.h-_bor * 2});

    // Clearing front edges
    _target.setDrawColor(_backColor);
    for (float y=0; y <= _rad+_bor; ++y) {
        for (float x=0; x < _rad+_bor; ++x) {
            if (sqr(y) + sqr(x) >= sqr(_rad-_bor)) {
                _target.drawPoint(_rad-x, _rad-y);
                _target.drawPoint(rect.w-_rad+x, _rad-y);
                _target.drawPoint(_rad-x, rect.h-_rad+y);
                _target.drawPoint(rect.w-_rad+x, rect.h-_rad+y);
            }
        }
    }

    // Clearing back edges
    _target.setDrawColor({255, 255, 255, 0});
    for (float y=0; y <= _rad; ++y) {
        for (float x=0; x <= _rad; ++x) {
            if (sqr(y) + sqr(x) > sqr(_rad)) {
                _target.drawPoint(_rad-x, _rad-y);
                _target.drawPoint(rect.w-_rad+x, _rad-y);
                _target.drawPoint(_rad-x, rect.h-_rad+y);
                _target.drawPoint(rect.w-_rad+x, rect.h-_rad+y);
            }
        }
    }

    // Setting texture for using
    SDL_UnlockTexture(texture);

    // Resetting render target
    _target.resetRenderTarget();
}

Backplate::~Backplate() {
    SDL_DestroyTexture(texture);
}
