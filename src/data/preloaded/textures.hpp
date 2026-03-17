/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../texturesNames.hpp"

#if (PRELOAD_TEXTURES)

#if (USE_SDL_IMAGE)
#include <SDL3_image/SDL_image.h>
#else
#error "Can't preload images without library"
#endif


// Class for load, draw and clear textures
class TexturesData {
 private:
    SDL_Texture* textures[unsigned(Textures::Count)];
    void loadTexture(SDL_Renderer* renderer, Textures name, const char* fileName);

 public:
    explicit TexturesData(SDL_Renderer* renderer);
    ~TexturesData();
    SDL_Texture* operator[] (Textures name) const;
};

#endif  // (PRELOAD_TEXTURES)
