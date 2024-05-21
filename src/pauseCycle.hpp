/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "cycleTemplate.hpp"
#include "GUI/baseGUI.hpp"


// Cycle for select settings variants
class PauseCycle : public CycleTemplate {
 private:
    // Variables
    timer nextSound = 0;  // Time to next play sound

    // GUI objects
    // Slider for set music volume
    GUI::Slider<Uint8> musicSlider{0.5, 0.75, data.musicVolume};
    // Slider for set sounds volume
    GUI::Slider<Uint8> soundSlider{0.5, 0.9, data.soundsVolume};
    // Flags for select language
    GUI::ImageButton flags[LNG_count] = {
        {0.3, 0.25, IMG_GUI_FLAG_USA},
        {0.7, 0.25, IMG_GUI_FLAG_RUS},
        {0.3, 0.5, IMG_GUI_FLAG_GER},
        {0.7, 0.5, IMG_GUI_FLAG_BEL},
    };
    // Button for quit settings menu
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    void draw() const override;                      // Drawing all needed objects
    void update() override;                          // Getting special objects update
    bool getMouseInput() override;                   // Checking for any mouse actions
    bool getKeysInput(SDL_Keysym& key) override;     // Checking for any keys actions
    bool getAnotherInput(SDL_Event& event) override;  // Getting all rest user input

 public:
    PauseCycle();   // Start pause cycle
};
