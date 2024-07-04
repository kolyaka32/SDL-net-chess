/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"


// Game cycle (for single player (special animation))
class SinglePlayerGameCycle : public BaseCycle {
 private:
    // Data for transition to animation
    Uint16 currentWidth = 8;
    Uint16 currentHeight = 8;

    // Data for board animation
    const ANI_names type = ANI_SINGLEPLAYER;
    const Uint16 width, height;   // Parameters of image
    Uint16 frame = 0;             // Current frame of animation
    timer prevFrameUpdate;        // Timer, when was last frame change

    // Main run functions
    bool getMouseInput() override;
    void update() override;
    void draw() const override;

 public:
    SinglePlayerGameCycle();
    ~SinglePlayerGameCycle();
};
