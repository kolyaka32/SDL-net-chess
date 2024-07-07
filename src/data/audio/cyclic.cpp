/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cyclic.hpp"
#include "../data.hpp"


MusicOrder::MusicOrder(MUS_names _start, Uint8 _count)
: currentMusicTrack(_start), first(_start), count(_count) {}

void MusicOrder::start() {
    // Playing first track only once to start
    data.playMusic(first, 1);
}

void MusicOrder::update() {
    // Checking, if music end
    if (Mix_PlayingMusic() == 0) {
        // Changing track
        currentMusicTrack++;
        if (currentMusicTrack >= first + count) {
            currentMusicTrack = first;
        }

        // Playing this track
        data.playMusic(currentMusicTrack, 1);
    }
}
