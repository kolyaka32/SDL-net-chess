#pragma once

#include "../dataTypes.hpp"
#include "dataLoader.hpp"

#define FNT_count 1  // Number of fonts for better count


// Library for work with fonts
class FontLibrary
{
public:
    FontLibrary();   // Initialasing font library
    ~FontLibrary();  // Closing font library
};


// Class of loaded fonts
class DrawFont
{
private:
    TTF_Font *font;
    textHeight height;
    // Font_type type;
public:
    DrawFont(SDL_RWops *data, textHeight _height);  // Creating new font for need purpose
    ~DrawFont();                      // Clearing data from font
    bool isNeed(textHeight _height);  // Check, if current font need
    TTF_Font* getFont();              // Give current font for use for draw
};


// Class of all loaded fonts for draw texts
class Font : virtual FontLibrary, protected virtual DataLoader
{
private:
    SDL_RWops *fontData;   // Pointer to data of font
    DrawFont *fonts[20];   // Array of pointers to all fonts
    Uint8 fontsCount = 0;  // Summary counter of all loaded fonts
    bool loadFont(const char *name);  // Loading font with need name
public:
    Font();   // Loading all need fonts
    ~Font();  // Clearing data from fonts

    // Creating font with need height for draw
    TTF_Font *createFont(textHeight size);
};
