/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"


// Game cycle (for single player (special animation))
class SinglePlayerGameCycle : public BaseCycle {
 private:
    App& app;

    // Volume from start of cycle to reset later
    unsigned startVolume;

    // Data for transition to animation
    Uint16 currentWidth = 8;
    Uint16 currentHeight = 8;

    // Data for board animation
    const IMG_Animation* animation;
    const Uint16 width, height;   // Parameters of image
    Uint16 frame = 0;             // Current frame of animation
    timer prevFrameUpdate;        // Timer, when was last frame change

    // Main run functions
    void getMouseInput(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    SinglePlayerGameCycle(App& app);
    ~SinglePlayerGameCycle();
};
