#pragma once

#include "include.hpp"
#include "graphics.hpp"

// Names of all images with related numbers
enum IMG_names{
    // Menu icones
    IMG_MENU_PAUSE,
    IMG_MENU_SCROLLER_BUTTON,
    IMG_MENU_SCROLLER_LINE,
    IMG_MENU_BUTTON,
    IMG_MENU_TYPE_BOX,

    // Flags in settings
    IMG_FLAG_USA,
    IMG_FLAG_RUS,

    //
    IMG_GREEN_CROSS,
    IMG_GREEN_CIRCLE,

    //
    IMG_RED_CROSS,
    IMG_RED_CIRCLE,

    //
    IMG_CELL
};

// Number of all images
#define IMG_count 12


//
class GraphicsLibrary
{
public:
    GraphicsLibrary();
    ~GraphicsLibrary();
};


//
class Textures : GraphicsLibrary
{
public:
    SDL_Texture* textures[IMG_count];  // Array of all textures
public:
    Textures();
    ~Textures();
};
