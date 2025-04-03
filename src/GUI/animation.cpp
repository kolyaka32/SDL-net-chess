/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */


#include "baseGUI.hpp"

using namespace GUI;

#if ANI_count
// GIF animation class
GIFAnimation::GIFAnimation(Window& _target, SDL_Rect _rect, ANI_names _type)
: dest(_dest), type(_type), frame(0), prevTick(0) {}

GIFAnimation::~GIFAnimation() {
    SDL_DestroyTexture(texture);
}

void GIFAnimation::blit(const Window& _target) {
    if (SDL_GetTicks() > prevTick) {
        static unsigned frame = (frame + 1) % Animations[type]->count;
        _target.destroy(texture);
        texture = _target.createTexture(Animations[type]->frames[frame], false);
        prevTick = SDL_GetTicks() + Animations[type]->delays[frame] / 2;
    }
}
#endif
