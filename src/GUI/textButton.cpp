/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


// Button class
GUI::TextButton::TextButton(const Window& _target, float _X, float _Y, const LanguagedText _texts, float _size,
    Color _color, Aligment _aligment)
: HighlightedStaticText(_target, _X, _Y, _texts, 1, _size, _color, _aligment),
backplate(_target, {rect.x-10, rect.y-1, rect.w+20, rect.h+4}, _size * 0.75, 3) {}

void GUI::TextButton::blit(const Window& _target) const {
    backplate.blit(_target);
    _target.blit(texture, rect);
}
