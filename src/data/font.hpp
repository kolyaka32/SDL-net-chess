/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>

#include "../dataTypes.hpp"
#include "dataLoader.hpp"

#define FNT_count 1  // Number of fonts for better count


// Library for work with fonts
class FontLibrary {
 public:
    FontLibrary();   // Initialasing font library
    ~FontLibrary();  // Closing font library
};


// Class of loaded fonts
class DrawFont {
 private:
    TTF_Font *font;
    const textHeight height;
    // const Font_type type;

 public:
    DrawFont(SDL_RWops *data, textHeight _height);  // Creating new font for need purpose
    ~DrawFont();                                    // Clearing data from font
    const bool isNeed(textHeight _height) const;    // Check, if current font need
    TTF_Font* getFont() const;                // Give current font for use for draw
};


// Class of all loaded fonts for draw texts
class Font : virtual FontLibrary, protected virtual DataLoader {
 private:
    SDL_RWops *fontData;                  // Pointer to data of font
    std::vector<DrawFont*> fonts;         // Vector with all fonts
    void loadFontData(const std::string name);  // Loading font with need name

 public:
    Font();   // Loading all need fonts
    ~Font();  // Clearing data from fonts

    // Creating font with need height for draw
    TTF_Font* createFont(textHeight size);
};
