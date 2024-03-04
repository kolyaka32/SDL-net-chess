#include "../include.hpp"
#include "sounds.hpp"

Sounds::Sounds(){

}

Sounds::~Sounds(){
    // Clearing all musics after work
    for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(sounds[i]);
    }
}
