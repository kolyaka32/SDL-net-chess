/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "music.hpp"
#include "sounds.hpp"

#if (USE_SDL_MIXER)


// Class for interact with any audio
class Audio {
 private:
    // Output device
    SDL_AudioDeviceID audioDeviceID;
    SDL_AudioDeviceID getAudioDeviceID();
    // Mixer for playing any audio
    MIX_Mixer* mixer;
    MIX_Mixer* openMixer();

 public:
    explicit Audio();
    ~Audio();

    // Global preloaded objects
    #if (PRELOAD_MUSIC)
    MusicData music;
    #endif

    #if (PRELOAD_SOUNDS)
    SoundsData sounds;
    #endif

    // Get/set master volume: 1.0f - is normal
    void setVolume(float volume);
    float getVolume() const;
};

// Global system for launch music tracks
extern Audio audio;

#endif  // (USE_SDL_MIXER)
