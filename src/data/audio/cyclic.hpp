/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "musics.hpp"

// Class of music order to play in loop
class MusicOrder {
 private:
    Uint8 currentMusicTrack;  // Current playing music track
    const Uint8 first;  // First music track
    const Uint8 count;  // Count of all music tracks

 public:
    MusicOrder(MUS_names start, Uint8 count);
    void start();   // Start current order
    void update();  // Check, if need to change track
};
