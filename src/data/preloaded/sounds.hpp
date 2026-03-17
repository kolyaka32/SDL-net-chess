/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../soundsNames.hpp"

#if (PRELOAD_SOUNDS)

#if (USE_SDL_MIXER)
#include <SDL3_mixer/SDL_mixer.h>
#else
#error "Can't preload sounds without library"
#endif


// Class for playing sound with need name
class SoundsData {
 private:
    MIX_Audio* sounds[unsigned(Sounds::Count)];
    MIX_Track* tracks[unsigned(Sounds::Count)];  // ! Should be optimised to use less tracks
    void loadSound(MIX_Mixer* mixer, unsigned index, const char* name);

 public:
    explicit SoundsData(MIX_Mixer* mixer);
    ~SoundsData();
    void play(Sounds name) const;
    // Get/set volume for all sounds: 1.0f - is normal
    void setVolume(float volume);
    float getVolume() const;
};

#endif  // (PRELOAD_SOUNDS)
