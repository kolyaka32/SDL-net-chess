/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../cycleTemplate.hpp"


//
class SinglePlayerGameCycle : public CycleTemplate {
 private:
    // Data for transition to animation
    Uint16 currentWidth = 8;
    Uint16 currentHeight = 8;

    // Data for board animation
    const ANI_names type = ANI_SINGLEPLAYER;
    const Uint16 width, height;   // Parameters of image
    Uint16 frame;                 // Current frame of animation
    timer prevFrameUpdate;        // Timer, when was last frame change

    // Main run functions
    void draw() const override;  // Draw all need objects
    void update() override;      // Getting special objects update (if need)

 public:
    SinglePlayerGameCycle();
    ~SinglePlayerGameCycle();
};
