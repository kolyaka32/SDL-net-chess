#include "include.hpp"
#include "graphics.hpp"



Graphics::Graphics(){

}

Graphics::~Graphics(){
    for(Uint8 i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(textures[i]);
    }
}

SDL_Texture *Graphics::operator[](unsigned num){
    return textures[num];
}

SDL_Texture *Graphics::operator[](IMG_names num){
    return textures[num];
}