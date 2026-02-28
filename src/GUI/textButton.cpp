/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::TextButton::TextButton(const Window& _window, float _X, float _Y, const LanguagedText&& _texts, float _size,
    Color _color, Aligment _aligment)
: HighlightedStaticText(_window, _X, _Y, std::move(_texts), 1, _size, _color, _aligment),
backplate(_window, {rect.x-10, rect.y-1, rect.w+20, rect.h+4}, _size * 0.75, 3) {}

GUI::TextButton::TextButton(TextButton&& _object) noexcept
: HighlightedStaticText(std::move(_object)),
backplate(std::move(_object.backplate)) {}

void GUI::TextButton::blit() const {
    backplate.blit();
    window.blit(texture, rect);
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
