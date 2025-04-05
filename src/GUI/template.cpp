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
bool GUItemplate::in(const Mouse mouse) const {
    return mouse.in(rect);
}
