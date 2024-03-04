#pragma once

#include "include.hpp"
#include "dataTypes.hpp"

#define FNT_count 1  // Number of fonts for better count


//
class FontLibrary
{
private:
    /* data */
public:
    FontLibrary();
    ~FontLibrary();
};


//
class Font : FontLibrary
{
private:
    char* data;   // Pointer to data of font
    Uint64 size;  // Size of font
public:
    Font();
    ~Font();

    // Function of creating font with need height
    TTF_Font *createFont(textHeight size);
};
