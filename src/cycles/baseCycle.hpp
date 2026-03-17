/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../GUI/interface.hpp"
#include "../menu/settingsMenu.hpp"


// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    SettingsMenu settings;  // Menu for change settings
    const GUI::ImageButton exitButton;  // Button for exit from mode

 public:
    BaseCycle(Window& _window);
    bool inputMouseDown() override;
    void update() override;
    void inputMouseUp() override;
    void inputMouseWheel(float _wheelY) override;
};
