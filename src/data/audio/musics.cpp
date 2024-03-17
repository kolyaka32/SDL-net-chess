#include "musics.hpp"


// Load all tracks
Musics::Musics(){
    // Resetting list of music tracks
    #if CHECK_CORRECTION
    memset(musics, 0, MUS_count * sizeof(*musics));
    #endif

    // Loading all sounds
    //loadMusic("mus/.mp3", MUS_);  // Template

    //loadMusic("mus/main_theme.mp3", MUS_MAIN_THEME);
    //loadMusic("mus/menu_theme.mp3", MUS_MENU_THEME);

    // Checking correction of loaded tracks
    #if CHECK_CORRECTION
    if(!checkCorrection()){
        printf("Wrong count of music");
        exit(ERR_FIL_MUS);
    }
    #endif

    // Setting start volume of music
    Mix_VolumeMusic(musicVolume);  
}

// Clear all data
Musics::~Musics(){
    // Stopping playing music
    Mix_PauseMusic();

    // Clearing all musics after work
    for(int i=0; i < MUS_count; ++i){
        // Clearing main music track
        Mix_FreeMusic(musics[i]);
        
        // Clearing data for it
        free(musicsData[i]->hidden.mem.base);
        SDL_RWclose(musicsData[i]);
    }
}

// Play need music track
void Musics::playMusic(MUS_names _index){
    Mix_PlayMusic(musics[_index], -1);
}

// Load track with need name
void Musics::loadMusic(char *_name, MUS_names _index){
    // Getting selected file data
    musicsData[_index] = loadObject(_name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if(!musicsData[_index]){
        printf("Error with loading music file '%s' at %u.", _name, _index);
        exit(ERR_FIL_MUS);
    }
    #endif

    // Creating music, setting in array and clearing data
    musics[_index] = Mix_LoadMUS_RW(musicsData[_index], 0);
};

// Check correction of loaded tracks
#if CHECK_CORRECTION
bool Musics::checkCorrection(){
    // Setting counter
    Uint8 count = 0;

    // Checking, if all music tracks exist
    for(Uint8 i = 0; i < MUS_count; ++i){
        if(musics[i]){
            count++;
        }
    }

    // Returing correction of loaded number
    return count == MUS_count;
};
#endif
