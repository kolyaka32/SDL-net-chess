/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_image/SDL_image.h>
#include "loader/dataLoader.hpp"


// Class for load, draw and clear animations
template <unsigned count>
class AnimationsData {
 private:
    IMG_Animation* animations[count];
    void load(const DataLoader& loader, unsigned index, const char* name);
 public:
    AnimationsData(const DataLoader& loader, const char* names[count]);
    ~AnimationsData();
    IMG_Animation* operator[] (unsigned index) const;
};
