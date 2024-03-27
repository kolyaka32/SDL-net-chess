#pragma once

#include "cycleTemplate.hpp"
#include "GUI/baseGUI.hpp"


//
class PauseCycle : public CycleTemplate
{
private:
    // Interactable part:
    // Buttons for start variants
    GUI::Slider<Uint8> musicSlider{0.5, 0.75, data.musicVolume};
    GUI::Slider<Uint8> soundSlider{0.5, 0.9, data.soundsVolume};
    GUI::ImageButton flags[LNG_count] = {
        {0.3, 0.25, IMG_GUI_FLAG_USA},
        {0.7, 0.25, IMG_GUI_FLAG_RUS},
        {0.3, 0.5, IMG_GUI_FLAG_GER},
        {0.7, 0.5, IMG_GUI_FLAG_BEL},
    };
    // Setting menu quit
    GUI::ImageButton settingButton{0.9, 0.1, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    void getInput() override;    // Getting all user input (keyboard, mouse...)
    Uint8 mouseInput() override;  // Checking for any need mouse action
    void draw() const override;     // Drawing all needed objects
public:
    PauseCycle();
    ~PauseCycle();
};
