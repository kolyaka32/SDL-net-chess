/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../game/SettingsMenu.hpp"

// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 protected:
    static SettingsMenu settings;  // Menu for change settings
    const static GUI::ImageButton exitButton;  // Button for exit from mode
 public:
    BaseCycle();
    void update(App& app) override;
    void getAnotherInput(App& app, const SDL_Event& event) override;
};
