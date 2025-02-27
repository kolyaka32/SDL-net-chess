/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;


TypeBox::TypeBox(const Window& _target, float _height, float _x, float _y, const char* _text)
: TypeField(_target, _height, _x, _y, _text, GUI::MIDLE_text, BLACK),
backTexture(_target.getTexture(IMG_GUI_TYPE_BOX)),
backRect({SCREEN_WIDTH*_x-backTexture->w/2, SCREEN_HEIGHT*_y-backTexture->h/2+2, float(backTexture->w), float(backTexture->h)}) {}

// Overrided function for draw text and backplate at screen
void TypeBox::blit() const {
    // Rendering background picture for better typing
    target.blit(backTexture, backRect);

    // Rendering text
    target.blit(texture, rect);

    // Rendering caret
    if (showCaret) {
        target.setDrawColor({50, 50, 50, 50});
        target.drawRect(caretRect);
    }
}

bool TypeBox::in(float mouseX, float mouseY) const {
    return ((mouseX > backRect.x && mouseX < backRect.x + backRect.w) &&
        (mouseY > backRect.y && mouseY < backRect.y + backRect.h));
}
