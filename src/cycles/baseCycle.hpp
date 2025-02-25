/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../game/SettingsMenu.hpp"

// Base cycle for use in any game mode
class BaseCycle : public CycleTemplate {
 private:
    static bool keepSettings;  // Flag for keep setting menu for change language

 protected:
    SettingsMenu settings;     // Menu for change settings
    const GUI::ImageButton exitButton;  // Button for exit from mode
    void setKeepSettings();    // Set keeping opening of settings menu for next launch

 public:
    BaseCycle(const Window& target);
    void update(App& app) override;
    void getAnotherInput(App& app, const SDL_Event& event) override;
};
