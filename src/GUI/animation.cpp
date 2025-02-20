/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */


#include "baseGUI.hpp"

using namespace GUI;

#if ANI_count
// GIF animation class
GIFAnimation::GIFAnimation(Window& _target, SDL_Rect _rect, ANI_names _type) {
    // Creating animation
    type = _type;
    rect = _rect;
    frame = 0;
    prevTick = 0;
}

GIFAnimation::~GIFAnimation() {
    SDL_DestroyTexture(texture);
}

void GIFAnimation::update(Window& _target) {
    if (getTime() > prevTick) {
        frame = (frame + 1) % data.animations[type]->count;
        texture = SDL_CreateTextureFromSurface(data.renderer, data.animations[type]->frames[frame]);
        prevTick = getTime() + data.animations[type]->delays[frame] / 10;
    }
}
#endif
