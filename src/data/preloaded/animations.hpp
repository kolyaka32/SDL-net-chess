/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../animationsNames.hpp"

#if (PRELOAD_ANIMATIONS)

#if (USE_SDL_IMAGE)
#include <SDL3_image/SDL_image.h>
#else
#error "Can't preload animations without library"
#endif


// Class for load, get and clear preloaded animations
class AnimationsData {
 private:
    IMG_Animation* animations[unsigned(Animations::Count)];
    void loadAnimation(Animations name, const char* fileName);

 public:
    explicit AnimationsData();
    ~AnimationsData();
    IMG_Animation* operator[] (Animations name) const;
};

#endif  // (PRELOAD_TEXTURES)
