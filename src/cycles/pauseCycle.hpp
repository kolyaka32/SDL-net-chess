/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../GUI/baseGUI.hpp"
#include "../game/background.hpp"


// Cycle for select settings variants
class PauseCycle : public BaseCycle {
 private:
    timer nextSound = 0;  // Time to play next sound
    MovingBackground background;

    // GUI objects
    GUI::StaticText titleText{"Pause\0Пауза\0Pause\0Паўза",
        30, 0.5, 0.1};
    GUI::StaticText musicText{"Music\0Музыка\0Die Musik\0Музыка",
        30, 0.5, 0.68};
    GUI::StaticText soundText{"Sounds\0Звуки\0Geräusche\0Гук",
        30, 0.5, 0.83};
    GUI::Slider musicSlider{0.5, 0.75, &data.musicVolume};
    GUI::Slider soundSlider{0.5, 0.9, &data.soundsVolume};

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
    void draw() const override;
    void update() override;
    bool getMouseInput() override;
    bool getAnotherInput(const SDL_Event& event) override;

 public:
    PauseCycle();   // Start pause cycle
};
