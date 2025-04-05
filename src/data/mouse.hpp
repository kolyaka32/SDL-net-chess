/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "SDL3/SDL_rect.h"

// Class of position of mouse on screen
class Mouse {
private:
    SDL_FPoint position;

public:
    Mouse();
    void updatePos();
    bool in(SDL_FRect rect) const;
    bool near(float x, float y) const;
    float getX() const;
    float getY() const;
};
