/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"
#include "../GUI/baseGUI.hpp"

const Uint16 c = SCREEN_HEIGHT;

// Class of menu with game settings
class SettingsMenu : public GUI::GUItemplate {
 private:
    bool active = false;  // Flag of showing current menu
    timer nextSound = 0;  // Time to play next sound
    Uint8 holdingSlider = 0;  // Index of holded slider

    // Button for enter and quit settings menu
    const GUI::ImageButton settingButton;
    // Background plate
    const GUI::Backplate background;
    // Title
    GUI::StaticText titleText;
    // Flags for select language
    const GUI::ImageButton flags[LNG_count];
    // Sliders and it texts
    GUI::StaticText musicText;
    GUI::StaticText soundText;
    //GUI::Slider musicSlider{0.5, 0.7, &data.musicVolume};
    //GUI::Slider soundSlider{0.5, 0.8, &data.soundsVolume};

 public:
    SettingsMenu(const Window& target);
    void blit(const Window& target) const override;
    bool click(int mouseX, int mouseY);
    void getAnotherInput(App& target, const SDL_Event& event);
    void update(App& target);
    void activate();
};
