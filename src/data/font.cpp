#include "font.hpp"
#include "../workCodes.hpp"


// Initializing fonts library
FontLibrary::FontLibrary(){
    if(TTF_Init()){
        #if CHECK_CORRECTION
        printf("Couldn't initialize font library: %s\n", TTF_GetError());
        exit(ERR_SDL_FFT);
        #endif
    }
}

// Closing font library
FontLibrary::~FontLibrary(){
	TTF_Quit();
}


// Creating new font for need purpose
DrawFont::DrawFont(SDL_RWops *data, textHeight _height){
    height = _height;

    // Setting to read file from start
    SDL_RWseek(data, 0, RW_SEEK_SET);

    // Creating new font
    font = TTF_OpenFontRW(data, 0, height);

    //font = TTF_OpenFont("fnt/Arial.ttf", height);
};

// Clearing data from font
DrawFont::~DrawFont(){
    TTF_CloseFont(font);
};

// Check, if current font need
bool DrawFont::isNeed(textHeight _height){
    return (height == _height); // && (type == _type);
};

// Give current font for use for draw
TTF_Font* DrawFont::getFont(){
    return font;
};


// Class of all loaded fonts for draw texts
// Loading all need fonts
Font::Font(){
    #if DEBUG
    memset(fonts, 0, sizeof(fonts[0])*20);
    #endif
    // Checking correction of loading current font
    if(loadFont("fnt/PTSans-Regular.ttf")){
        #if CHECK_CORRECTION
        printf("Can't load data for fonts");
        exit(ERR_FIL_FNT);
        #endif
    }
}

// Clearing data from fonts
Font::~Font(){
    // Clearing created fonts
    for(Uint8 i=0; i < fontsCount; ++i){
        delete fonts[i];
    }

    // Clearing data from font creating
    //free(fontData->hidden.mem.base);
    SDL_FreeRW(fontData);
}

// Creating font with need height for draw
TTF_Font *Font::createFont(textHeight _size){
    // Searching for already excisting font with need size
    for(Uint8 i=0; i < fontsCount; ++i){
        if(fonts[i]->isNeed(_size)){
            return fonts[i]->getFont();
        }
    }
    // Creating new font
    fonts[fontsCount] = new DrawFont(fontData, _size);
    fontsCount++;
    return fonts[fontsCount-1]->getFont();
};

// Loading font with need name
bool Font::loadFont(const char *name){
    // Openning font file
    fontData = loadObject(name);

    // Checking correction of file
    return (fontData == nullptr);
}