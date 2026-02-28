/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "music.hpp"

#if (PRELOAD_MUSIC)

#include "loader/loader.hpp"


MusicData::MusicData(MIX_Mixer* _mixer) {
    // Resetting all tracks
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        musics[i] = nullptr;
    }
    #endif

    // Loading all needed music tracks
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        loadMusic(_mixer, Music(i), musicFilesNames[i]);
    }

    // Creating option for infinite music play
    playOption = SDL_CreateProperties();
    SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_LOOPS_NUMBER, -1);

    // Creating tracks for switchy play
    tracks[0] = MIX_CreateTrack(_mixer);
    tracks[1] = MIX_CreateTrack(_mixer);

    // Setting music volume
    setVolume(0.5f);

    // Checking massive on loading correction
    #if (CHECK_CORRECTION)
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        if (musics[i] == NULL) {
            logImportant("Don't load music: %s", musicFilesNames[i]);
            return;
        }
    }
    logAdditional("Music loaded corretly");
    #endif
}

MusicData::~MusicData() {
    // Destrying option
    SDL_DestroyProperties(playOption);

    // Closing all audios and tracks
    for (unsigned i=0; i < unsigned(Music::Count); ++i) {
        MIX_DestroyAudio(musics[i]);
    }
    // Clearing tracks
    MIX_DestroyTrack(tracks[0]);
    MIX_DestroyTrack(tracks[1]);
}

void MusicData::loadMusic(MIX_Mixer* _mixer, Music _index, const char* _name) {
    // Load data of current music track
    SDL_IOStream* iodata = dataLoader.load(_name);

    // Loading track
    musics[unsigned(_index)] = MIX_LoadAudio_IO(_mixer, iodata, false, true);

    // Checking correction of loaded music
    #if (CHECK_CORRECTION)
    if (musics[unsigned(_index)] == nullptr) {
        logImportant("Can't create music: %s", _name);
        return;
    }
    #endif
}

void MusicData::start(Music _index) {
    // Check, if already playing it
    if (currentPlay != musics[unsigned(_index)]) {
        // Stop playing current track
        MIX_StopTrack(tracks[currentTrack], 0);

        // Updating current track position
        currentTrack = 1 - currentTrack;
        currentPlay = musics[unsigned(_index)];

        // Setting on another track new music
        MIX_SetTrackAudio(tracks[currentTrack], musics[unsigned(_index)]);

        // Resetting fading
        SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_FADE_IN_FRAMES_NUMBER, 0);
        SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_START_MILLISECOND_NUMBER, 0);

        // Infinite playing new selected track withiou fading
        MIX_PlayTrack(tracks[currentTrack], playOption);
    }
}

void MusicData::startFading(Music _index) {
    // Check, if already playing it
    if (currentPlay != musics[unsigned(_index)]) {
        // Stop playing current track (with fade out)
        MIX_StopTrack(tracks[currentTrack], fadeFrames);

        // Updating current track position
        currentTrack = 1 - currentTrack;
        currentPlay = musics[unsigned(_index)];

        // Setting on another track new music
        MIX_SetTrackAudio(tracks[currentTrack], musics[unsigned(_index)]);

        // Setting fading
        SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_FADE_IN_FRAMES_NUMBER, fadeFrames);
        SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_START_MILLISECOND_NUMBER, 0);

        // Infinite playing new selected track with fade in
        MIX_PlayTrack(tracks[currentTrack], playOption);
    }
}

void MusicData::startFromCurrent(Music _index) {
    // Check, if already playing it
    if (currentPlay != musics[unsigned(_index)]) {
        // Stop playing current track (with fade out)
        MIX_StopTrack(tracks[currentTrack], fadeFrames);

        // Getting current position in that track
        Sint64 framePosition = MIX_GetTrackPlaybackPosition(tracks[currentTrack]);

        // Updating current track position
        currentTrack = 1 - currentTrack;
        currentPlay = musics[unsigned(_index)];

        // Setting on another track new music
        MIX_SetTrackAudio(tracks[currentTrack], musics[unsigned(_index)]);

        // Setting fading
        SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_FADE_IN_FRAMES_NUMBER, fadeFrames);
        SDL_SetNumberProperty(playOption, MIX_PROP_PLAY_LOOP_START_FRAME_NUMBER, framePosition);

        // Infinite playing new selected track with fade in
        MIX_PlayTrack(tracks[currentTrack], playOption);
    }
}

void MusicData::setVolume(float _volume) {
    MIX_SetTrackGain(tracks[0], _volume);
    MIX_SetTrackGain(tracks[1], _volume);
}

float MusicData::getVolume() const {
    return MIX_GetTrackGain(tracks[0]);
}

#endif  // (PRELOAD_MUSIC)
