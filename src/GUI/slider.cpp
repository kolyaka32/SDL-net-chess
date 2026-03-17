/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)


GUI::Slider::Slider(const Window& _window, float _X, float _Y, float _width, float _startValue,
    Textures _lineImage, Textures _buttonImage)
: TextureTemplate(_window, _window.getTexture(_lineImage)) {
    // Getting need texture
    buttonTexture = _window.getTexture(_buttonImage);
    rect.w = _window.getWidth() * _width;
    rect.h = texture->h * rect.w / texture->w;
    buttonRect.w = buttonTexture->w * rect.w / texture->w;
    buttonRect.h = buttonTexture->h * rect.w / texture->w;

    // Setting it to need place
    rect.x = _window.getWidth() * _X - rect.w / 2;
    rect.y = _window.getHeight() * _Y - rect.h / 2;
    buttonRect.y = _window.getHeight() * _Y - buttonRect.h / 2;
    buttonRect.x = rect.x + rect.w * _startValue - buttonRect.w / 2;
}

GUI::Slider::Slider(Slider&& _object) noexcept
: TextureTemplate(std::move(_object)) {
    buttonTexture = _object.buttonTexture;
    buttonRect = _object.buttonRect;
}

float GUI::Slider::setValue(float _mouseX) {
    // Setting new position
    buttonRect.x = _mouseX;

    // Setting borders for position
    setMax(buttonRect.x, rect.x + rect.w);
    setMin(buttonRect.x, rect.x);

    float value = (buttonRect.x - rect.x)/rect.w;
    buttonRect.x -= buttonRect.w / 2;

    return value;
}

float GUI::Slider::scroll(float _wheelY) {
    if (_wheelY > 0) {
        return setValue(buttonRect.x + buttonRect.w/2 + rect.w / 16);
    } else {
        return setValue(buttonRect.x + buttonRect.w/2 - rect.w / 16);
    }
    return 0;
}

void GUI::Slider::blit() const {
    window.blit(texture, rect);
    window.blit(buttonTexture, buttonRect);
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
