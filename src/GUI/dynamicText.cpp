/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::DynamicText::DynamicText(const Window& _window, float _X, float _Y,
    LanguagedText&& _texts, float _height, Color _color, Aligment _aligment)
: TextureTemplate(_window),
texts(std::move(_texts)),
posX(_X),
aligment(_aligment),
color(_color),
height(_height) {
    // Creating surface with text
    texture = window.createTexture(Fonts::Main, height, texts.getString().c_str(), 0, color);

    // Moving draw rect to new place
    rect.w = texture->w;
    rect.h = texture->h;
    rect.x = SDL_roundf(window.getWidth() * _X - (rect.w * (unsigned)_aligment / 2));
    rect.y = SDL_roundf(window.getHeight() * _Y - rect.h / 2);
}

GUI::DynamicText::DynamicText(DynamicText&& _object) noexcept
: TextureTemplate(std::move(_object)),
texts(_object.texts),
posX(_object.posX),
aligment(_object.aligment),
color(_object.color),
height(_object.height) {}

GUI::DynamicText::~DynamicText() noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
