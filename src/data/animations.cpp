/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "animations.hpp"


Animations::Animations(const DataLoader& _loader, unsigned _count, const char* _filesNames[]) {
    // Resetting texture masiive
    #if CHECK_CORRECTION
    for (unsigned i=0; i < _count; ++i) {
        animations[i] = nullptr;
    }
    #endif

    // Loading all needed textures
    for (unsigned i=0; i < _count; ++i) {
        load(_loader, i, _filesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < _count; ++i) {
        if (animations[i] == NULL) {
            throw DataLoadException("Animation: " + std::string(_filesNames[i]));
        }
    }
    #endif
}

Animations::~Animations() {
    // Closing all used textures
    for (unsigned i=0; i < ANI_count; ++i) {
        IMG_FreeAnimation(animations[i]);
    }
}

void Animations::load(const DataLoader& _loader, unsigned _index, const char* _name) {
    // Load data
    SDL_IOStream* iodata = _loader.load(_name);

    // Loading animation
    animations[_index] = IMG_LoadAnimation_IO(iodata, true);

    // Checking correction of loaded animation
    #if CHECK_CORRECTION
    if (animations[_index] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif
}

IMG_Animation* Animations::operator[] (ANI_names _index) const {
    return animations[_index];
}
