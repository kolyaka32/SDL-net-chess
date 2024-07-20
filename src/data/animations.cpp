/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "animations.hpp"
#include "loadExceptions.hpp"

#if ANI_count

// Animation base class
// Loading all needed animations
Animations::Animations() {
    // Resetting list of textures
    #if CHECK_CORRECTION
    memset(animations, 0, ANI_count * sizeof(animations[0]));
    #endif

    // Loading all animations
    // loadAnimation(".gif", ANI_);  // Template

    loadAnimation("singlePlayer.gif", ANI_SINGLEPLAYER);  // Template

    // Checking correction of all loaded animations
    #if CHECK_CORRECTION
    checkCorrection();
    #endif
}

//
Animations::~Animations() {
    // Unloading all gif animations
    for (int i=0; i < ANI_count; ++i) {
        IMG_FreeAnimation(animations[i]);
    }
}

//
void Animations::loadAnimation(const std::string _name, ANI_names _index) {
    // Getting selected animation data
    SDL_RWops *tempRW = loadObject("ani/" + _name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if (!tempRW) {
        throw DataLoadException{"animation file load: " + _name};
    }
    #endif

    // Creating animation and setting it to need place, freeing loading data
    animations[_index] = IMG_LoadAnimation_RW(tempRW, 1);

    // Checking correction of loaded animation
    #if CHECK_CORRECTION
    if (animations[_index] == nullptr) {
        throw DataLoadException{"animation file creation: " + _name};
    }
    #endif
}

// Checking, if all animations loaded (if need)
#if CHECK_CORRECTION
void Animations::checkCorrection() {
    // Setting counter
    Uint8 count = 0;

    // Checking, if all images exist
    for (Uint8 i = 0; i < ANI_count; ++i) {
        if (animations[i]) {
            count++;
        }
    }

    // Check, if all objects correct
    if (count != ANI_count) {
        throw DataLoadException{"wrong count of animations"};
    }
}
#endif

#endif
