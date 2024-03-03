#include "include.hpp"
#include "font.hpp"


Font::Font(){

}

Font::~Font(){
    free(data);
}

TTF_Font *Font::createFont(textHeight _size){
    SDL_RWops* RWopsData = SDL_RWFromMem(data, size);
    return TTF_OpenFontRW(RWopsData, 1, _size);
};