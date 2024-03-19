#include "font.hpp"
#include "../workCodes.hpp"


//
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


//
Font::Font(){
    // Checking correction of loading current font
    if(!loadFont("fnt/Arial.ttf")){
        printf("Can't load font");
        exit(ERR_FIL_FNT);
    }
}

//
Font::~Font(){
    // Claering data for font creating
    free(fontData->hidden.mem.base);
    SDL_FreeRW(fontData);
}

//
TTF_Font *Font::createFont(textHeight _size){
    // Setting to read file from start
    SDL_RWseek(fontData, 0, RW_SEEK_SET);

    // Creating new font
    return TTF_OpenFontRW(fontData, 0, _size);
};

//
bool Font::loadFont(const char *name){
    // Openning font file
    fontData = loadObject(name);

    // Checking correction of file
    return (fontData != nullptr);
}