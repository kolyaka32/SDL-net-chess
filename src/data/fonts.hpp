/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "SDL_ttf.h"
#include "loader/dataLoader.hpp"
#include "../fontsNames.hpp"

typedef unsigned short textHeight;

// Class for draw any font with need height
class Fonts
{
private:
    /* data */
public:
    Fonts(DataLoader loader);
    ~Fonts();
};

