/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../fontsNames.hpp"

#if (PRELOAD_FONTS)

#if (USE_SDL_FONT)
#include <SDL3_ttf/SDL_ttf.h>
#else
#error "Can't preload fonts without library"
#endif


// Class for get font with need height
class FontsData {
 private:
    TTF_Font* fonts[unsigned(Fonts::Count)];
    void loadFont(Fonts index, const char* fileName);

 public:
    FontsData();
    ~FontsData();
    TTF_Font* operator[](Fonts index) const;
};

#endif  // (PRELOAD_FONTS)
