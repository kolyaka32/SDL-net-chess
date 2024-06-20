/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../include.hpp"
#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;

// Tempate function for resetting texture
GUItemplate::GUItemplate() {
    texture = nullptr;
}

// Template function for draw
void GUItemplate::blit() const {
    SDL_RenderCopy(data.renderer, texture, NULL, &rect);
}

// Template function for check, if mouse press in object
bool GUItemplate::in(const int mouseX, const int mouseY) const {
    return ((mouseX > rect.x && mouseX < rect.x + rect.w) &&
        (mouseY > rect.y && mouseY < rect.y + rect.h));
}

// Template for updating location of current object
void GUItemplate::updateLocation() {}
