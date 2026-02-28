/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)


GUI::Animation::Animation(const Window& _window, float _X, float _Y, float _W, float _H, Animations _type)
: Animation(_window, {_X*window.getWidth(), _Y*window.getHeight(), _W*window.getWidth(), _H*window.getHeight()}, _type) {}

GUI::Animation::Animation(const Window& _window, const SDL_FRect& _dest, Animations _type)
: TextureTemplate(_window, _dest),
type(_type),
animation(window.getAnimation(_type)),
frame(0),
prevTick(getTime() + animation->delays[0]) {
    texture = _window.createTexture(animation->frames[0]);
}

GUI::Animation::Animation(Animation&& _object) noexcept
: TextureTemplate(std::move(_object)),
type(_object.type),
animation(_object.animation),
frame(_object.frame),
prevTick(_object.prevTick) {}

GUI::Animation::~Animation() noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void GUI::Animation::update() {
    if (SDL_GetTicks() > prevTick) {
        frame = (frame + 1) % animation->count;
        SDL_DestroyTexture(texture);
        texture = window.createTexture(animation->frames[frame]);
        prevTick = getTime() + animation->delays[frame];
    }
}

#endif  // (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
