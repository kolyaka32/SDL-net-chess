#pragma once

#include "include.hpp"

// Types of data
typedef Uint8 coord;       // Type of data for 1 coordinate of cell
typedef Uint8 position;    // Type of data for position in array (2 coordinats)
typedef Uint8 cell;        // Type of cell content
typedef Uint8 byte;        // Type for saving any side-data (like archieve)
typedef Uint16 count;      // Type of data for any counters

typedef Uint64 timer;      // Type of data for time (SDL_GetTicks64())
typedef Uint8 textHeight;  // Type of heights of any letters
