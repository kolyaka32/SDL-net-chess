/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


// Tempate function for resetting texture
GUI::GUItemplate::GUItemplate() {
    texture = nullptr;
}

// Template function for draw
void GUI::GUItemplate::blit(const Window& _target) const {
    _target.blit(texture, rect);
}

// Template function for check, if mouse press in object
bool GUI::GUItemplate::in(const Mouse mouse) const {
    return mouse.in(rect);
}
