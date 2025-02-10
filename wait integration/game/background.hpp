/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


//
class MovingBackground {
 private:
    const Uint8 maxIndex = 33;  // Maximal index, if greater - reset
    Uint16 offset = 0;  // Offset (in pixels) for moving background
    Uint8 index = 0;    // Index of drawing line (for figures)

 public:
    MovingBackground();
    void blit() const;
    void update();
};
