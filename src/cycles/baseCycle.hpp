/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../game/SettingsMenu.hpp"

//
class BaseCycle : public CycleTemplate {
 protected:
    Uint8 selectedBox;      // Number of which box is currently selected
    const MUS_names music;  // Music track to play (or NULL, if not need start)
    SettingsMenu settings;     // Menu for change settings
    const GUI::ImageButton exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};
 public:
    BaseCycle(MUS_names song = MUS_START_NONE);
    void update() override;
    bool getAnotherInput(const SDL_Event& event) override;
};
