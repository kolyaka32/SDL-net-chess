/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include "loader/dataLoader.hpp"


// Class for draw any font with need height
template <unsigned count>
class FontsData {
private:
    TTF_Font* fonts[count];
    void loadFont(const DataLoader& loader, unsigned index, const char* name);
public:
    FontsData(const DataLoader& loader, const char* filesNames[]);
    ~FontsData();
    TTF_Font* operator[](unsigned index) const;
};
