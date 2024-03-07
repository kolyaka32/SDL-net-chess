#pragma once

#include "include.hpp"
#include "dataTypes.hpp"
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
class Font : FontLibrary, public DataLoader
{
private:
    SDL_RWops *fontData;   // Pointer to data of font

    bool loadFont(const char *name);
public:
    Font();
    ~Font();

    // Function of creating font with need height
    TTF_Font *createFont(textHeight size);
};
