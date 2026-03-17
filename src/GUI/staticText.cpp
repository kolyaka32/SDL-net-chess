/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::StaticText::StaticText(StaticText&& _object) noexcept
: TextureTemplate(std::move(_object)) {}

GUI::StaticText::~StaticText() noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
