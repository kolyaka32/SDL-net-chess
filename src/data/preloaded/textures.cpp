/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "textures.hpp"


template <unsigned count>
TexturesData<count>::TexturesData(const DataLoader& _loader, SDL_Renderer* _renderer, const char* _filesNames[count]) {
    // Resetting texture masiive
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        textures[i] = nullptr;
    }
    #endif

    // Loading all needed textures
    for (unsigned i=0; i < count; ++i) {
        loadTexture(_loader, _renderer, i, _filesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        if (textures[i] == NULL) {
            throw DataLoadException("Texture at index: " + std::to_string(i));
        }
    }
    #endif
}

template <unsigned count>
TexturesData<count>::~TexturesData() {
    // Closing all used textures
    for (unsigned i=0; i < count; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

template <unsigned count>
void TexturesData<count>::loadTexture(const DataLoader& _loader, SDL_Renderer* _renderer, unsigned _index, const char* _name) {
    // Load data of current texture
    SDL_IOStream* iodata = _loader.load(_name);

    // Creating surface
    SDL_Surface* surface = IMG_Load_IO(iodata, true);

    // Checking correction of created surface
    #if CHECK_CORRECTION
    if (surface == nullptr) {
        throw DataLoadException(_name);
    }
    #endif

    // Creating texture
    textures[_index] = SDL_CreateTextureFromSurface(_renderer, surface);

    // Checking correction of loaded texture
    #if CHECK_CORRECTION
    if (textures[_index] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif

    SDL_DestroySurface(surface);
}

template <unsigned count>
SDL_Texture* TexturesData<count>::operator[] (unsigned index) const {
    return textures[index];
}
