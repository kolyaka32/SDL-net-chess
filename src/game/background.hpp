/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/baseGUI.hpp"


// Class of menu moving background
class MovingBackground : GUI::GUItemplate {
 private:
    const Uint8 maxIndex = 33;  // Maximal index, if greater - reset
    static Uint16 offset;       // Offset (in pixels) for moving background
    static Uint8 index;         // Index of drawing line (for figures)

 public:
    MovingBackground();
    void blit(const Window& target) const override;
    void update();
};
