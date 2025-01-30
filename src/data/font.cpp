/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "font.hpp"
#include "loadExceptions.hpp"


// Initializing fonts library
FontLibrary::FontLibrary() {
    if (TTF_Init()) {
        #if CHECK_CORRECTION
        throw LibararyLoadException("font library");
        #endif
    }
}

// Closing font library
FontLibrary::~FontLibrary() {
    TTF_Quit();
}


// Creating new font for need purpose
DrawFont::DrawFont(SDL_RWops *data, textHeight _height) : height(_height) {
    // Setting to read file from start
    SDL_RWseek(data, 0, RW_SEEK_SET);

    // Creating new font
    font = TTF_OpenFontRW(data, 0, height);
}

// Clearing data from font
DrawFont::~DrawFont() {
    TTF_CloseFont(font);
}

// Check, if current font need
const bool DrawFont::isNeed(textHeight _height) const {
    return (height == _height);  // && (type == _type);
}

// Give current font for use for draw
TTF_Font* DrawFont::getFont() const {
    return font;
}


// Class of all loaded fonts for draw texts
// Loading all need fonts
Font::Font() {
    // Loading only font
    loadFontData("fnt/PTSans-Regular.ttf");
}

// Clearing data from fonts
Font::~Font() {
    // Clearing created fonts
    for (Uint8 i=0; i < fonts.size(); ++i) {
        delete fonts[i];
    }
    // Clear list of all fonts
    fonts.clear();

    // Clearing data from font creating
    // free(fontData->hidden.mem.base);
    SDL_FreeRW(fontData);
}

// Creating font with need height for draw
TTF_Font* Font::createFont(textHeight _size) {
    // Searching for already excisting font with need size
    for (Uint8 i=0; i < fonts.size(); ++i) {
        if (fonts[i]->isNeed(_size)) {
            return fonts[i]->getFont();
        }
    }
    // Creating new font
    fonts.push_back(new DrawFont(fontData, _size));

    return fonts[fonts.size()-1]->getFont();
}

// Loading font with need name
void Font::loadFontData(const std::string _name) {
    // Openning font file
    fontData = loadObject(_name);

    // Check, if loaded normaly
    #if CHECK_CORRECTION
    if (fontData == nullptr) {
        throw DataLoadException("font file: " + _name);
    }
    #endif
}
