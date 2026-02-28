/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/background.hpp"


// Cycle for select variants to start
class SelectCycle : public BaseCycle {
 protected:
    MovingBackground background;
    // Texts
    GUI::HighlightedStaticText titleText;
    GUI::TextButton singleplayerButton;
    GUI::TextButton twoPlayerButton;
    GUI::TextButton serverButton;
    GUI::TextButton connectButton;

 protected:
    bool inputMouseDown() override;
    void inputKeys(SDL_Keycode key) override;
    void update() override;
    void draw() const override;

 public:
    SelectCycle(Window& window);
};
