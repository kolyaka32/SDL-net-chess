/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../musicNames.hpp"

#if (PRELOAD_MUSIC)

#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#else
#error "Can't preload music without library"
#endif


// Class for play music
class MusicData {
 private:
    // Preloaded undecoed music tracks to be played
    MIX_Audio* musics[unsigned(Music::Count)];
    // Tracks, where music will be played (sitching between them)
    MIX_Track* tracks[2];
    int currentTrack;  // Currently selected track track (can be 0/1)
    // Index of currently playing track
    MIX_Audio* currentPlay = nullptr;
    // Option for play music forever
    SDL_PropertiesID playOption;
    // Static timers for fade in/out for music
    static const Sint64 fadeFrames = 20000;
    void loadMusic(MIX_Mixer* mixer, Music index, const char* name);

 public:
    explicit MusicData(MIX_Mixer* mixer);
    ~MusicData();
    void start(Music name);
    void startFading(Music name);
    void startFromCurrent(Music name);
    // Get/set volume for all music: 1.0f - is normal
    void setVolume(float volume);
    float getVolume() const;
};

#endif  // (PRELOAD_MUSIC)
