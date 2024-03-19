#include "animations.hpp"
#include "../workCodes.hpp"

#if ANI_count

//
Animations::Animations(){
    // Resetting list of textures
    memset(animations, 0, ANI_count * sizeof(animations[0]));

    // Loading all animations
    //loadAnimation("ani/.gif", ANI_);  // Template


    // Checking correction of all loaded animations
    if(!checkCorrection()){
        printf("Wrong count of animations");
        exit(ERR_FIL_ANI);
    }
}

//
Animations::~Animations(){
    // Unloading gif animations
    for(int i=0; i < ANI_count; ++i){
        IMG_FreeAnimation(animations[i]);
    }
}

//
void Animations::loadAnimation(const char *_name, ANI_names _index){
    // Getting selected animation data
    SDL_RWops *tempRW = loadObject(_name);

    // Checking correction of loaded data
    if(!tempRW){
        printf("Error with loading animation file '%s' at %u.", _name, _index);
        exit(ERR_FIL_IMG);
    }

    // Creating animation and setting it to need place, freeing loading data
    animations[_index] = IMG_LoadAnimation_RW(tempRW, 1);
};

// 
bool Animations::checkCorrection(){
    // Setting counter
    Uint8 count = 0;

    // Checking, if all images exist
    for(Uint8 i = 0; i < ANI_count; ++i){
        if(animations[i]){
            count++;
        }
    }

    // Returing correction of loaded number
    return count == IMG_count;
};

#endif
