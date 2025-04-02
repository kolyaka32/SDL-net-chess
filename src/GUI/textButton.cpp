/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;


// Button class
TextButton::TextButton(const Window& _target, const std::string (&_text)[LNG_count], float _size, float _X, float _Y,
    Color _color, ALIGNMENT_types _alignment)
: HighlightedStaticText(_target, _text, _size, _X, _Y, 1, _color, _alignment),
backplate(_target, {rect.x-10, rect.y-1, rect.w+20, rect.h+4}, _size * 0.75, 3) {}

void TextButton::blit(const Window& _target) const {
    backplate.blit(_target);
    _target.blit(texture, rect);
}
