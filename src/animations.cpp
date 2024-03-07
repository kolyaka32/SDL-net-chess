#include "include.hpp"
#include "animations.hpp"

#if ANI_count

Animation::Animation(){

}

Anumation::~Animation(){
    // Unloading gif animations
    for(int i=0; i < ANI_count; ++i){
        IMG_FreeAnimation(Animations[i]);
    }
}


// Animations functions
static counter loadedAnimations;
// Function of loading selected GIF animation
static void loadAnimation(const char* name, ANI_names number){
    // Getting selected animation data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating animation from data
    Animations[number] = IMG_LoadAnimation_RW(tempRW, 0);
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Animations[number] != NULL){
        loadedAnimations++;
    };
};

if(loadAllAnimations() != ANI_count){
    printf("Wrong count of animations");
    exit(ERR_FIL_ANI);
}

// Animations functions

// Loading all animations
inline unsigned loadAllAnimations(){
    loadedAnimations = 0;  // Resseting counter
    //loadAnimation("ani/.gif", ANI_);

    // Returning numbers of loaded files
    return loadedAnimations;
};

static counter loadedAnimations;
// Function of loading selected GIF animation
static void loadAnimation(const char* name, ANI_names number){
    // Creating animation from data
    Animations[number] = IMG_LoadAnimation(name);

    // Checking correction of loaded file
    if(Animations[number] != NULL){
        loadedAnimations++;
    };
};

#endif
