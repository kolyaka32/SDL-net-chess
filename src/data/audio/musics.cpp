/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "musics.hpp"


// Class of working with music
Musics::Musics() {
    // Resetting list of music tracks
    #if CHECK_CORRECTION
    memset(musics, 0, MUS_count * sizeof(*musics));
    #endif

    // Loading all sounds
    // loadMusic(".mp3", MUS_);  // Template

    loadMusic("menu.mp3", MUS_MENU_THEME);
    loadMusic("main-1.mp3", MUS_MAIN_1);
    loadMusic("main-2.mp3", MUS_MAIN_2);
    loadMusic("main-3.mp3", MUS_MAIN_3);
    loadMusic("singleplayer.mp3", MUS_SINGLEPLAYER);

    // Checking correction of loaded tracks
    #if CHECK_CORRECTION
    checkCorrection();
    #endif

    // Setting start volume of music
    Mix_VolumeMusic(musicVolume);
}

Musics::~Musics() {
    // Stopping playing music
    Mix_PauseMusic();

    // Clearing all musics after work
    for (int i=0; i < MUS_count; ++i) {
        // Clearing main music track
        Mix_FreeMusic(musics[i]);

        // Clearing data from track
        #if ARCHIEVE_LOADING
        free(musicsData[i]->hidden.mem.base);
        #endif

        // Closing data
        SDL_RWclose(musicsData[i]);
    }
}

void Musics::playMusic(Uint8 track, int times) {
    Mix_PlayMusic(musics[track - 1], times);
}

void Musics::loadMusic(const std::string _name, const MUS_names _index) {
    // Getting selected file data
    musicsData[_index - 1] = loadObject("mus/" + _name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if (!musicsData[_index - 1]) {
        throw DataLoadException("music file load: " + _name);
    }
    #endif

    // Creating music, setting in array and clearing data
    musics[_index - 1] = Mix_LoadMUS_RW(musicsData[_index - 1], 0);

    // Checking correction of loaded music
    #if CHECK_CORRECTION
    if (musics[_index - 1] == nullptr) {
        throw DataLoadException("music file creation: " + _name);
    }
    #endif
}

#if CHECK_CORRECTION
void Musics::checkCorrection() {
    // Checking, if all music tracks exist
    for (Uint8 i = 0; i < MUS_count; ++i) {
        if (musics[i] == NULL) {
            throw DataLoadException("wrong count");
        }
    }
}
#endif
