/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "SDL_image.h"

#include "loader/dataLoader.hpp"
#include "../texturesNames.hpp"

// Class for load, draw and clear textures
class Textures
{
private:
    unsigned count = 0;
    SDL_Texture* textures[50];
    void loadTexture();
public:
    Textures(const DataLoader& loader);
    ~Textures();
    SDL_Texture* operator[] (IMG_names index);
};
