/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "testing.hpp"


// Global flags of compilation
// External libraries linkage
#define USE_SDL_IMAGE        true   // Library for load external images from disk
#define USE_SDL_MIXER        true   // Library for play sounds/music
#define USE_SDL_FONT         true   // Library for draw text at screen
#define USE_NET              true   // Any of libraries for use with internet connection
#define USE_LIBZIP           true   // Library for compress data to zip archives
// Use setting file for store data between seccions  
#define USE_SETTING_FILE     true
// Preloaded GFX (could be created runtime)
#define PRELOAD_TEXTURES     true   // Preload textures
#define PRELOAD_ANIMATIONS   true   // Preload GIF animaions
#define PRELOAD_FONTS        true   // Preload fonts
#define PRELOAD_SOUNDS       true   // Preload sounds
#define PRELOAD_MUSIC        true   // Preload music
// Use archive for store additional GFX
#define PRELOAD_DATA PRELOAD_TEXTURES | PRELOAD_FONTS | PRELOAD_ANIMATIONS | PRELOAD_SOUNDS | PRELOAD_MUSIC
// Additional flags
#define CAPTURE_AUIO         false  // Flag of using audio capture device


// System game name
#define WINDOW_NAME "Chess on SDL"
#define LOG_NAME "log.txt"

// Game field parameters
#define FIELD_WIDTH 8  // Number of cells
#define CELL_SIDE 64   // Width and height of cell in pixels
// ! Should be removed
#define GAME_WIDTH FIELD_WIDTH * CELL_SIDE  // Width of game area
#define GAME_HEIGHT GAME_WIDTH              // Height of game area
#define LETTER_LINE 20                      // Place for letters for field
#define UPPER_LINE (90 + LETTER_LINE)       // Extra place for better UI options
#define LEFT_LINE LETTER_LINE               // Place for field letters
#define RIGHT_LINE LETTER_LINE              // Place for field letters
#define DOWN_LINE LETTER_LINE               // Place for field letters
#define WINDOW_WIDTH (GAME_WIDTH + LEFT_LINE + RIGHT_LINE)    // Width of all screen
#define WINDOW_HEIGHT (GAME_HEIGHT + UPPER_LINE + DOWN_LINE)  // Height of all screen

// Base file names
// File with all GFX
#if (PRELOAD_DATA)
#define DATA_FILE "data-chess.dat"
#endif

// File with all saved data (language, settings, volumes...)
#if (USE_SETTING_FILE)
#define SETTING_FILE "settings-chess.ini"
#endif

// Number of active connections in internet part
#if (USE_NET)
#define MAX_CONNECTIONS 1
#define BASE_PORT 8000
#define BROADCAST_INDEX 3
#define BROADCAST_PORT 5667
#endif  // (USE_NET)
