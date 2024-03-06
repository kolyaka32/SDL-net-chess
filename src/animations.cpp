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

#endif
