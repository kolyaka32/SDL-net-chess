/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/selectingMenu/selectingMenu.hpp"


// Creating two player mode (standart game)
class TwoPlayerGameCycle : public GameCycle {
 protected:
   SelectingMenu menu;

 protected:
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode _key) override;
    void update() override;
    void draw() const override;

 public:
    TwoPlayerGameCycle(Window& window);
};
