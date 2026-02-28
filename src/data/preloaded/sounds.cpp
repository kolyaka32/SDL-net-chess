/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "sounds.hpp"

#if (PRELOAD_SOUNDS)

#include "loader/loader.hpp"


SoundsData::SoundsData(MIX_Mixer* _mixer) {
    // Resetting all sounds
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        sounds[i] = nullptr;
    }
    #endif

    // Loading all needed sounds
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        loadSound(_mixer, i, soundsFilesNames[i]);
    }

    // Resetting sounds volume
    setVolume(0.5f);

    // Checking massive on loading correction
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        if (sounds[i] == NULL) {
            logImportant("Don't load sound: %s", soundsFilesNames[i]);
        }
    }
    logAdditional("Sounds loaded corretly");
    #endif
}

SoundsData::~SoundsData() {
    // Closing all sounds
    for (unsigned i=0; i < unsigned(Sounds::Count); ++i) {
        MIX_DestroyTrack(tracks[i]);
        MIX_DestroyAudio(sounds[i]);
    }
}

void SoundsData::loadSound(MIX_Mixer* _mixer, unsigned _index, const char* _name) {
    // Load data of current sound
    SDL_IOStream* iodata = dataLoader.load(_name);

    // Loading sound without encoding
    sounds[_index] = MIX_LoadAudio_IO(_mixer, iodata, false, true);

    // Checking of correction of loaded sound
    #if (CHECK_CORRECTION)
    if (sounds[_index] == nullptr) {
        logImportant("Can't create sound: %s", _name);
        return;
    }
    #endif

    // Creating own track
    tracks[_index] = MIX_CreateTrack(_mixer);

    // Checking of correction of created track
    #if (CHECK_CORRECTION)
    if (tracks[_index] == nullptr) {
        logImportant("Can't create track: %s", _name);
        return;
    }
    #endif

    // Setting separate track to play different sounds
    MIX_SetTrackAudio(tracks[_index], sounds[_index]);
}

void SoundsData::play(Sounds _index) const {
    MIX_PlayTrack(tracks[unsigned(_index)], 0);
}

void SoundsData::setVolume(float _volume) {
    for (int i=0; i < unsigned(Sounds::Count); ++i) {
        MIX_SetTrackGain(tracks[i], _volume);
    }
}

float SoundsData::getVolume() const {
    return MIX_GetTrackGain(tracks[0]);
}

#endif  // (PRELOAD_SOUNDS)
