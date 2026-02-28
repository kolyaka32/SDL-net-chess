/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::RoundedBackplate::RoundedBackplate(const Window& _window, float _centerX, float _centerY, float _width, float _height,
    float _rad, float _bor, Color _frontColor, Color _backColor)
: RoundedBackplate(_window, {_window.getWidth() * (_centerX - _width/2), _window.getHeight() * (_centerY - _height/2),
    _window.getWidth() * _width, _window.getHeight() * _height}, _rad, _bor, _frontColor, _backColor) {}


GUI::RoundedBackplate::RoundedBackplate(const Window& _window, const SDL_FRect& _rect, float _rad, float _bor, Color _frontColor, Color _backColor)
: TextureTemplate(_window, _rect, _window.createTexture(_rect.w, _rect.h)) {
    // Setting render target to this texture
    window.setRenderTarget(texture);

    // Drawing back part
    window.setDrawColor(_backColor);
    window.clear();

    // Drawing front part
    window.setDrawColor(_frontColor);
    window.drawRect({_bor, _bor, rect.w-_bor * 2, rect.h-_bor * 2});

    // Clearing front edges
    window.setDrawColor(_backColor);
    for (float y=0; y <= _rad+_bor; ++y) {
        for (float x=0; x < _rad+_bor; ++x) {
            if (sqr(y) + sqr(x) >= sqr(_rad-_bor)) {
                window.drawPoint(_rad-x, _rad-y);
                window.drawPoint(rect.w-_rad+x, _rad-y);
                window.drawPoint(_rad-x, rect.h-_rad+y);
                window.drawPoint(rect.w-_rad+x, rect.h-_rad+y);
            }
        }
    }

    // Clearing back edges
    window.setDrawColor({255, 255, 255, 0});
    for (float y=0; y <= _rad; ++y) {
        for (float x=0; x <= _rad; ++x) {
            if (sqr(y) + sqr(x) > sqr(_rad)) {
                window.drawPoint(_rad-x, _rad-y);
                window.drawPoint(rect.w-_rad+x, _rad-y);
                window.drawPoint(_rad-x, rect.h-_rad+y);
                window.drawPoint(rect.w-_rad+x, rect.h-_rad+y);
            }
        }
    }

    // Setting texture for using
    SDL_UnlockTexture(texture);

    // Resetting render target
    window.resetRenderTarget();
}

GUI::RoundedBackplate::RoundedBackplate(RoundedBackplate&& _object) noexcept
: TextureTemplate(std::move(_object)) {}

GUI::RoundedBackplate::~RoundedBackplate() noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
