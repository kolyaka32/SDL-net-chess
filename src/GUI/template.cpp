/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;

// Tempate function for resetting texture
GUItemplate::GUItemplate() {
    texture = nullptr;
}

// Template function for draw
void GUItemplate::blit(const Window& _target) const {
    _target.blit(texture, rect);
}

// Template function for check, if mouse press in object
bool GUItemplate::in(float mouseX, float mouseY) const {
    return ((mouseX > rect.x && mouseX < rect.x + rect.w) &&
        (mouseY > rect.y && mouseY < rect.y + rect.h));
}
