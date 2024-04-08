#pragma once

#include "dataLoader.hpp"

// Names of all images with related numbers
enum IMG_names{
    // Base part
    // Graphic interface sprites
    IMG_GUI_PAUSE_BUTTON,
    IMG_GUI_SLIDER_BUTTON,
    IMG_GUI_SLIDER_LINE,
    IMG_GUI_BASE_BUTTON,
    IMG_GUI_TYPE_BOX,

    // Base flags in settings
    IMG_GUI_FLAG_USA,
    IMG_GUI_FLAG_RUS,
    IMG_GUI_FLAG_GER,
    IMG_GUI_FLAG_BEL,

    // Main game part
    // Game field
    IMG_GAME_FIELD,

    // Game figures
    // White figures
    IMG_GAME_WHITE_PAWN,
    IMG_GAME_WHITE_BISHOP,
    IMG_GAME_WHITE_ROOK,
    IMG_GAME_WHITE_KNIGHT,
    IMG_GAME_WHITE_QUEEN,
    IMG_GAME_WHITE_KING,

    // Black figures
    IMG_GAME_BLACK_PAWN,
    IMG_GAME_BLACK_BISHOP,
    IMG_GAME_BLACK_ROOK,
    IMG_GAME_BLACK_KNIGHT,
    IMG_GAME_BLACK_QUEEN,
    IMG_GAME_BLACK_KING,

    // Point, where figure can go
    IMG_GAME_POINT_MOVE_TO,
};

// Number of all images
#define IMG_count 23


// Library for work with any images
class GraphicsLibrary
{
public:
    GraphicsLibrary();   // Initialasing graphic library
    ~GraphicsLibrary();  // Closing graphic library
};


// Class of all loaded textures for use
class Textures : virtual GraphicsLibrary, public virtual DataLoader
{
private:
    // Loading texture with need name
    void loadTexture(const char *name, IMG_names index);

    #if CHECK_CORRECTION
    void checkCorrection();  // Check, if all objects load correct
    #endif
public:
    SDL_Texture *textures[IMG_count];  // Array of all textures
    Textures();   // Loading all data, need for work with textures
    ~Textures();  // Clear all data from textures
};
