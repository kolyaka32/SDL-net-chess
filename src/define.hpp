/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// System numbers
#define WINDOWNAME "Chess on SDL"           // System game name
// Game field parameters
#define FIELD_WIDTH 8                       // Number of cells
#define CELL_SIDE 64                        // Width and height of cell in pixels
// Widthes and heightes
#define GAME_WIDTH FIELD_WIDTH * CELL_SIDE  // Width of game area
#define GAME_HEIGHT GAME_WIDTH              // Height of game area
#define LETTER_LINE 20                      // Place for letters for field
#define UPPER_LINE (90 + LETTER_LINE)       // Extra place for better UI options
#define LEFT_LINE LETTER_LINE               // Place for field letters
#define RIGHT_LINE LETTER_LINE              // Place for field letters
#define DOWN_LINE LETTER_LINE               // Place for field letters
#define SCREEN_WIDTH (GAME_WIDTH + LEFT_LINE + RIGHT_LINE)  // Width of all screen
#define SCREEN_HEIGHT (GAME_HEIGHT + UPPER_LINE + DOWN_LINE)  // Height of all screen

// Internet constants
#define BASE_PORT 2000                      // Base port to create/connect
#define INTERNET_BUFFER 5                   // Size of data to send/recieve by connecion
#define MAX_SEND_ID 128                     // Maximal number of send message ID
#define MESSAGE_GET_TIMEOUT 4000            // Time after which connection is considered lost
#define MESSAGE_NULL_TIMEOUT 800            // Time to send NULL message to keep connecion
#define MESSAGE_APPLY_TIMEOUT 600           // Time to apply arriving message
#define CONNECTION_LOST_PERCENT 50

// Base file names
#define SETTING_FILE "settings5.ini"        // File with all starting data (width, height...)
#define DATA_FILE "data5.dat"               // File with all GFX

// Global game colors
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}
#define GREY {175, 175, 175, 255}
#define FIELD_LIGHT {255, 206, 158, 255}
#define FIELD_DARK {206, 139, 71, 255}

// Macroses
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define SET_MIN(value, min) (value = value < min ? min : value)
#define SET_MAX(value, max) (value = value > max ? max : value)
#define sqr(value) ((value) * (value))
