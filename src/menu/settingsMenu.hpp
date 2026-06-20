/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Class of menu with game settings
class SettingsMenu : public GUI::SubWindow {
 private:
    timer nextSound = 0;      // Time to play next sound
    Uint8 holdingSlider = 0;  // Index of holded slider

    // Button for enter and quit settings menu
    const GUI::ImageButton settingButton;
    // Main part
    GUI::HighlightedStaticText titleText;
    const GUI::ImageButton flags[(unsigned)Language::Count];
    // Sliders for music (if need)
    #if (PRELOAD_MUSIC)
    GUI::HighlightedStaticText musicText;
    GUI::Slider musicSlider;
    #endif
    // Slider for sounds (if need)
    #if (PRELOAD_SOUNDS)
    GUI::HighlightedStaticText soundText;
    GUI::Slider soundSlider;
    #endif
    GUI::TextButton exitButton;

 public:
    explicit SettingsMenu(const Window& window);
    void blit() const;
    bool click(const Mouse mouse);
    void unClick();
    bool scroll(const Mouse mouse, float wheelY);
    void update();
};
