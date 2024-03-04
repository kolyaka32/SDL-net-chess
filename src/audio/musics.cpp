#include "../include.hpp"
#include "musics.hpp"

Musics::Musics(){

}

Musics::~Musics(){
    // Clearing all musics after work
    for(int i=0; i < MUS_count; ++i){
        // Clearing main music track
        Mix_FreeMusic(musics[i]);
        
        // Clearing data for music track
        SDL_RWclose(musicsData[i]);
    }
}
