/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include "loader/dataLoader.hpp"
#include "../fontsNames.hpp"

// Class for draw any font with need height
class Fonts {
private:
    TTF_Font* fonts[FNT_count];
    void loadFont(const DataLoader& loader, unsigned index, const char* name);
public:
    Fonts(const DataLoader& loader, unsigned count, const char* filesNames[]);
    ~Fonts();
    TTF_Font* operator[](FNT_names index) const;
};
