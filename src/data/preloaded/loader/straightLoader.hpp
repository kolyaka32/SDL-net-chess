/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../define.hpp"


// Check, if need to load data straight from files
#if (PRELOAD_DATA) && !(ARCHIEVE_LOADING)

#include <SDL3/SDL_iostream.h>


// Class of simplier implimintation of loading file, straight from file
class StraightLoader {
 public:
    SDL_IOStream* load(const char* name) const;
};

#endif  // (PRELOAD_DATA) && !(ARCHIEVE_LOADING)
