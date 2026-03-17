/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


GUI::RectBackplate::RectBackplate(const Window& _window, float _centerX, float _centerY, float _width, float _height,
    float _border, Color _frontColor, Color _backColor)
: RectBackplate(_window, {_window.getWidth() * (_centerX - _width/2), _window.getHeight() * (_centerY - _height/2),
    _window.getWidth() * _width, _window.getHeight() * _height}, _border, _frontColor, _backColor) {}

GUI::RectBackplate::RectBackplate(const Window& _window, const SDL_FRect& _rect, float _border,
    Color _frontColor, Color _backColor)
: TextureTemplate(_window, _rect, _window.createTexture(_rect.w, _rect.h)) {
    // Rendering backplate
    window.setRenderTarget(texture);
    window.setDrawColor(GREY);
    window.clear();
    window.setDrawColor(WHITE);
    window.drawRect({_border, _border, rect.w-2*_border, rect.h-2*_border});
    window.resetRenderTarget();
}

GUI::RectBackplate::RectBackplate(const RectBackplate& _object) noexcept
: TextureTemplate(_object.window, _object.rect, _object.window.createTexture(_object.rect.w, _object.rect.h)) {
    window.copyTexture(texture, _object.texture);
}

GUI::RectBackplate::RectBackplate(RectBackplate&& _object) noexcept
: TextureTemplate(std::move(_object)) {}

GUI::RectBackplate::~RectBackplate() noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
