/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_image/SDL_image.h>

#include "loader/dataLoader.hpp"
#include "../texturesNames.hpp"

// Class for load, draw and clear textures
class Textures {
private:
    SDL_Texture* textures[IMG_count];
    void loadTexture();
public:
    Textures(const DataLoader& loader, unsigned count, const char* names[]);
    ~Textures();
    SDL_Texture* operator[] (IMG_names index);
};
