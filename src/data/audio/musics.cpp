/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "musics.hpp"


// Load all tracks
Musics::Musics() {
    // Resetting list of music tracks
    #if CHECK_CORRECTION
    memset(musics, 0, MUS_count * sizeof(*musics));
    #endif

    // Loading all sounds
    // loadMusic("mus/.mp3", MUS_);  // Template

    loadMusic("mus/main_theme.mp3", MUS_MAIN_THEME);
    loadMusic("mus/menu_theme.mp3", MUS_MENU_THEME);

    // Checking correction of loaded tracks
    #if CHECK_CORRECTION
    checkCorrection();
    #endif

    // Setting start volume of music
    Mix_VolumeMusic(musicVolume);
}

// Clear all data
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

// Play need music track
void Musics::playMusic(MUS_names _index) {
    Mix_PlayMusic(musics[_index - 1], -1);
}

// Load track with need name
void Musics::loadMusic(const char *_name, const MUS_names _index) {
    // Getting selected file data
    musicsData[_index - 1] = loadObject(_name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if (!musicsData[_index - 1]) {
        SDL_Log("Error with loading music file '%s' at %u.", _name, _index - 1);
        exit(ERR_FIL_MUS);
    }
    #endif

    // Creating music, setting in array and clearing data
    musics[_index - 1] = Mix_LoadMUS_RW(musicsData[_index - 1], 0);

    // Checking correction of loaded music
    #if CHECK_CORRECTION
    if (musics[_index - 1] == nullptr) {
        SDL_Log("Error with loading music file '%s' at %u.", _name, _index - 1);
        exit(ERR_FIL_MUS);
    }
    #endif
}

// Check correction of loaded tracks
#if CHECK_CORRECTION
void Musics::checkCorrection() {
    // Checking, if all music tracks exist
    for (Uint8 i = 0; i < MUS_count; ++i) {
        if (musics[i] == NULL) {
            SDL_Log("Wrong music track at %u.", i);
            exit(ERR_FIL_MUS);
        }
    }
}
#endif
