/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/baseGUI.hpp"
#include "../data/data.hpp"

const Uint16 c = SCREEN_HEIGHT;

// Class of menu with game settings
class SettingsMenu : public GUI::GUItemplate {
 private:
    bool active = false;  // Flag of showing current menu
    timer nextSound = 0;  // Time to play next sound
    Uint8 holdingSlider = 0;  // Index of holded slider

    // Button for enter and quit settings menu
    const GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};
    // Background plate
    const GUI::Backplate background{0.5, 0.5, 0.65, 0.7, 20, 5};
    // Title
    GUI::StaticText titleText{"Pause\0Пауза\0Pause\0Паўза",
        30, 0.5, 0.2};
    // Flags for select language
    const GUI::ImageButton flags[LNG_count] = {
        {0.35, 0.33, IMG_GUI_FLAG_USA},
        {0.65, 0.33, IMG_GUI_FLAG_RUS},
        {0.35, 0.53, IMG_GUI_FLAG_GER},
        {0.65, 0.53, IMG_GUI_FLAG_BEL},
    };
    // Sliders and it texts
    GUI::StaticText musicText{"Music\0Музыка\0Die Musik\0Музыка",
        30, 0.5, 0.65};
    GUI::StaticText soundText{"Sounds\0Звуки\0Geräusche\0Гук",
        30, 0.5, 0.75};
    GUI::Slider musicSlider{0.5, 0.7, &data.musicVolume};
    GUI::Slider soundSlider{0.5, 0.8, &data.soundsVolume};

 public:
    SettingsMenu();
    void blit() const override;
    bool click(int mouseX, int mouseY);
    void getAnotherInput(const SDL_Event& event);
    void update();
    void activate();
};
