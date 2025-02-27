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
    void loadTexture(const DataLoader& _loader, SDL_Renderer* renderer, unsigned _index, const char* _name);
public:
    Textures(const DataLoader& loader, SDL_Renderer* renderer, unsigned count, const char* names[]);
    ~Textures();
    SDL_Texture* operator[] (IMG_names index) const;
};
