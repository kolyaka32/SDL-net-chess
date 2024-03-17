#include "sounds.hpp"


// Loading all sounds
Sounds::Sounds(){
    // Resetting list of sounds
    #if CHECK_CORRECTION
    memset(sounds, 0, SND_count * sizeof(*sounds));
    #endif

    // Loading all sounds
    //loadSound("snd/.wav", SND_);  // Template

    //loadSound("snd/click.wav", SND_CLICK);
    //loadSound("snd/flagSet.wav", SND_FLAG_SET);
    //loadSound("snd/loose.wav", SND_LOOSE);
    //loadSound("snd/win.wav", SND_WIN);

    // Checking correction of loading
    #if CHECK_CORRECTION
    if(!checkCorrection()){
        printf("Wrong count of sounds");
        exit(ERR_FIL_SND);
    }
    #endif

    // Setting start volume of effects
    Mix_Volume(-1, soundsVolume);
}

// Clearing all musics after work
Sounds::~Sounds(){
    for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(sounds[i]);
    }
}

// Play need sound
void Sounds::playSound(SND_names _index){
    Mix_PlayChannel(-1, sounds[_index], 1);
}

// Load sound with need name
void Sounds::loadSound(char *_name, SND_names _index){
    // Getting selected file data
    SDL_RWops *tempRW = loadObject(_name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if(!tempRW){
        printf("Error with loading sound file '%s' at %u.", _name, _index);
        exit(ERR_FIL_SND);
    }
    #endif

    // Creating sound, setting in array and clearing data
    sounds[_index] = Mix_LoadWAV_RW(tempRW, 0);

    // Freeing data from sound
    free(tempRW->hidden.mem.base);
    SDL_RWclose(tempRW);
};

// Check correction of loaded sounds
#if CHECK_CORRECTION
bool Sounds::checkCorrection(){
    // Setting counter
    Uint8 count = 0;

    // Checking, if all sounds exist
    for(Uint8 i = 0; i < SND_count; ++i){
        if(sounds[i]){
            count++;
        }
    }

    // Returing correction of loaded number
    return count == SND_count;
};
#endif
