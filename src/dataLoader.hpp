#pragma once

#include "include.hpp"
#include "define.hpp"
#include "values.hpp"

// Load file with all data
void loadData();

// Function of clearing all temporary data, loaded from arcieve
void unloadData();

// Archive values
#define PASSWORD NULL  // Archive password

// Used numerated numbers
#define ICO_count 1  // Number of icones for better count
#define FNT_count 1  // Number of fonts for better count

// Names of images in array to using
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
#define IMG_count 12

// Names of music in array to use
enum MUS_names{

};
#define MUS_count 0

// Names of sound effects in array to use
enum SND_names{

};
#define SND_count 0

// Names of animations in array to use
enum ANI_names{

};
#define ANI_count 0
