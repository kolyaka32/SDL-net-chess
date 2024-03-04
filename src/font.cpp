#include "include.hpp"
#include "font.hpp"
#include "workCodes.hpp"


FontLibrary::FontLibrary(){
    // Initializing fonts library
    if(TTF_Init()){
        printf("Couldn't initialize font library: %s\n", TTF_GetError());
        exit(ERR_SDL_FFT);
    }
}

FontLibrary::~FontLibrary(){
    // Closing font library
	TTF_Quit();
}


Font::Font(){
    
}

Font::~Font(){
    free(data);
}

TTF_Font *Font::createFont(textHeight _size){
    SDL_RWops* RWopsData = SDL_RWFromMem(data, size);
    return TTF_OpenFontRW(RWopsData, 1, _size);
};