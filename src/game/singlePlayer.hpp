/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../cycleTemplate.hpp"


//
class SinglePlayerGameCycle : public CycleTemplate {
 private:
    // Extra GUI
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};
    GUI::ImageButton exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};

    // Data for transition to animation
    Uint16 currentWidth = 8;
    Uint16 currentHeight = 8;

    // Data for board animation
    const ANI_names type = ANI_SINGLEPLAYER;
    const Uint16 width, height;   // Parameters of image
    Uint16 frame = 0;             // Current frame of animation
    timer prevFrameUpdate;        // Timer, when was last frame change

    // Main run functions
    bool getMouseInput() override;    // Getting mouse clicking
    void update() override;      // Getting special objects update (if need)
    void draw() const override;  // Draw all need objects

 public:
    SinglePlayerGameCycle();
    ~SinglePlayerGameCycle();
};
