/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::RoundedBackplate::RoundedBackplate(const Window& _window, float _centerX, float _centerY, float _width, float _height,
    int _rad, int _bor, Color _frontColor, Color _backColor)
: RoundedBackplate(_window, {_window.getWidth() * (_centerX - _width/2), _window.getHeight() * (_centerY - _height/2),
    _window.getWidth() * _width, _window.getHeight() * _height}, _rad, _bor, _frontColor, _backColor) {}


GUI::RoundedBackplate::RoundedBackplate(const Window& _window, const SDL_FRect& _rect, int _rad, int _bor, Color _frontColor, Color _backColor)
: TextureTemplate(_window, _rect, _window.createTexture(_rect.w, _rect.h)) {
    // Setting render target to this texture
    window.setRenderTarget(texture);

    // Drawing back part
    window.setDrawColor(_backColor);
    window.clear();

    // Drawing front part
    window.setDrawColor(_frontColor);
    window.drawRect({float(_bor), float(_bor), rect.w-_bor * 2, rect.h-_bor * 2});

    // Draw rounded corners
    int x = 0;
    int r1 = _rad;
    int y1 = _rad;
    int m1 = 5 - 4 * r1;
    int r2 = _rad - _bor;
    int y2 = r2;
    int m2 = 5 - 4 * r2;
    while (x <= y1) {
        window.setDrawColor(_backColor);
        for (int xx = r1 - y1; xx < r1 - y2; xx++) {
            window.drawPoint(xx,          r1 - x);
            window.drawPoint(rect.w - xx, r1 - x);
            window.drawPoint(xx,          rect.h - r1 + x);
            window.drawPoint(rect.w - xx, rect.h - r1 + x);
        }
        window.setDrawColor(TRANSPARENT);
        for (int xx = 0; xx < r1 - y1; xx++) {
            window.drawPoint(xx,          r1 - x);
            window.drawPoint(rect.w - xx, r1 - x);
            window.drawPoint(xx,          rect.h - r1 + x);
            window.drawPoint(rect.w - xx, rect.h - r1 + x);
        }

        if (m2 > 0 && x < y2) {
            window.setDrawColor(_backColor);
            for (int xx = 0; xx < r1 - x; xx++) {
                window.drawPoint(xx,          r1 - y2);
                window.drawPoint(rect.w - xx, r1 - y2);
                window.drawPoint(xx,          rect.h - r1 + y2);
                window.drawPoint(rect.w - xx, rect.h - r1 + y2);
            }
            y2--;
            m2 -= 8 * y2;
        }
        if (m1 > 0) {
            window.setDrawColor(TRANSPARENT);
            for (int xx = 0; xx < r1 - x; xx++) {
                window.drawPoint(xx,          r1 - y1);
                window.drawPoint(rect.w - xx, r1 - y1);
                window.drawPoint(xx,          rect.h - r1 + y1);
                window.drawPoint(rect.w - xx, rect.h - r1 + y1);
            }
            y1--;
            m1 -= 8 * y1;
        }
        x++;
        m1 += 8 * x + 4;
        m2 += 8 * x + 4;
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
