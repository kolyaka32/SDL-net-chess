/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>

#include "graphics.hpp"
#include "dataLoader.hpp"


// Total animation counter
#define ANI_count 1

// Data for work with animations
#if ANI_count

// Names of sound effects in array to use
enum ANI_names{
     ANI_SINGLEPLAYER,
};

// Base class with all animations
class Animations : virtual GraphicsLibrary, public virtual DataLoader {
 public:
    IMG_Animation *animations[ANI_count];  // List with all animations

 private:
    // Function for load animation with need name
    void loadAnimation(const std::string name, ANI_names index);
    // Check, if all animations load correctly (if need)
    #if CHECK_CORRECTION
    void checkCorrection();
    #endif

 public:
    Animations();
    ~Animations();
};
#endif
