#include "musics.hpp"


//
Musics::Musics(){
    // Resetting list of music tracks
    memset(musics, 0, MUS_count * sizeof(musics[0]));

    // Loading all sounds
    //loadMusic("mus/.mp3", MUS_);  // Template

    //loadMusic("mus/main_theme.mp3", MUS_MAIN_THEME);
    //loadMusic("mus/menu_theme.mp3", MUS_MENU_THEME);

    // Checking correction of loading
    if(!checkCorrection()){
        printf("Wrong count of music");
        exit(ERR_FIL_MUS);
    }

    // Setting start volume of music
    Mix_VolumeMusic(MusicVolume);  
}

//
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

//
void Musics::playMusic(MUS_names _index){
    Mix_PlayMusic(musics[_index], -1);
}

//
void Musics::loadMusic(char *_name, MUS_names _index){
    // Getting selected file data
    musicsData[_index] = loadObject(_name);

    // Checking correction of loaded data
    if(!musicsData[_index]){
        printf("Error with loading music file '%s' at %u.", _name, _index);
        exit(ERR_FIL_MUS);
    }

    // Creating music, setting in array and clearing data
    musics[_index] = Mix_LoadMUS_RW(musicsData[_index], 0);
};

//
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