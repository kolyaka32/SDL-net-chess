/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "animations.hpp"


template <unsigned count>
AnimationsData<count>::AnimationsData(const DataLoader& _loader, const char* _filesNames[count]) {
    // Resetting texture masiive
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        animations[i] = nullptr;
    }
    #endif

    // Loading all needed textures
    for (unsigned i=0; i < count; ++i) {
        load(_loader, i, _filesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < count; ++i) {
        if (animations[i] == NULL) {
            throw DataLoadException("Animation: " + std::string(_filesNames[i]));
        }
    }
    #endif
}

template <unsigned count>
AnimationsData<count>::~AnimationsData() {
    // Closing all used textures
    for (unsigned i=0; i < count; ++i) {
        IMG_FreeAnimation(animations[i]);
    }
}

template <unsigned count>
void AnimationsData<count>::load(const DataLoader& _loader, unsigned _index, const char* _name) {
    // Checking correction of trying to load
    #if CHECK_CORRECTION
    if (_name == nullptr) {
        throw DataLoadException(_name);
    }
    #endif

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

template <unsigned count>
IMG_Animation* AnimationsData<count>::operator[] (unsigned _index) const {
    return animations[_index];
}
