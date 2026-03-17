/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_rect.h>
#include "logger.hpp"


// Class of position of mouse on screen
class Mouse {
 private:
    SDL_FPoint position;
    SDL_MouseButtonFlags state;

 public:
    Mouse();
    void updatePos();
    bool in(SDL_FRect rect) const;
    bool near(float x, float y) const;
    float getX() const;
    float getY() const;
    SDL_MouseButtonFlags getState() const;
};
