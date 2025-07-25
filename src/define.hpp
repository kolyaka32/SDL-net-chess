/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// System name
#define WINDOW_NAME "Chess on SDL"

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
#define WINDOW_WIDTH (GAME_WIDTH + LEFT_LINE + RIGHT_LINE)    // Width of all screen
#define WINDOW_HEIGHT (GAME_HEIGHT + UPPER_LINE + DOWN_LINE)  // Height of all screen

// Internet constants
#define BASE_PORT 8000                      // Base port to create/connect
#define MAX_SEND_ID 128                     // Maximal number of send message ID
#define MESSAGE_GET_TIMEOUT 5000            // Time after which connection is considered lost
#define MESSAGE_APPLY_TIMEOUT 2000          // Time to send apply message to keep connecion
#define MESSAGE_RESEND_TIMEOUT 250          // Time after which need to resend message, as it was lost
#define CONNECTION_LOST_PERCENT 0           // Option for better testing of connection stability

// Base file names
#define SETTING_FILE "settings-chess.ini"   // File with all starting data (width, height...)
#define DATA_FILE "chess.dat"               // File with all GFX
