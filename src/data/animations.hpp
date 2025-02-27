/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_image/SDL_image.h>

#include "loader/dataLoader.hpp"
#include "../animationsNames.hpp"


// Class for load, draw and clear animations
class Animations {
 private:
    IMG_Animation* animations[ANI_count];
    void load(const DataLoader& _loader, unsigned _index, const char* _name);
 public:
    Animations(const DataLoader& loader, unsigned count, const char* names[]);
    ~Animations();
    IMG_Animation* operator[] (ANI_names index) const;
};
