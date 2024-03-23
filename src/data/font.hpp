#pragma once

#include "../dataTypes.hpp"
#include "dataLoader.hpp"

#define FNT_count 1  // Number of fonts for better count


//
class FontLibrary
{
public:
    FontLibrary();
    ~FontLibrary();
};


//
class DrawFont
{
private:
    TTF_Font *font;
    textHeight height;
    // Font_type type;
public:
    DrawFont(SDL_RWops *data, textHeight _height);
    ~DrawFont();
    bool isNeed(textHeight _height);
    TTF_Font* getFont();
};


//
class Font : virtual FontLibrary, protected virtual DataLoader
{
private:
    SDL_RWops *fontData;    // Pointer to data of font
    DrawFont *fonts[20];  // Array of pointers to fonts
    Uint8 fontsCount = 0;   // 
    bool loadFont(const char *name);
public:
    Font();
    ~Font();

    // Function of creating font with need height
    TTF_Font *createFont(textHeight size);
};
