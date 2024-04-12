#pragma once

// Debuging modifiers
#define DEBUG true
#define CHECK_CORRECTION DEBUG
#define ARCHIEVE_LOADING !DEBUG
#define SCROLLER_SOUND SND_count
#define CONNECTION_LOST_PERCENT 60

// System numbers
#define WINDOWNAME "Chess on SDL"           // System game name
#define FIELD_WIDTH 8                       // Number of cells
#define CELL_SIDE 64                        // Width and height of mine in pixels
#define GAME_WIDTH FIELD_WIDTH * CELL_SIDE  // Width of game area
#define GAME_HEIGHT GAME_WIDTH              // Height of game area
#define SCREEN_WIDTH (GAME_WIDTH)           // Width of all screen
#define SCREEN_HEIGHT (GAME_HEIGHT)         // Height of all screen

// Internet numbers
#define BASE_PORT 2000                      // Base port to create/connect
#define INTERNET_BUFFER 5                   // Size of data to send/recieve by connecion
#define MESSAGE_GET_TIMEOUT 2000            // Time after which connection is considered lost
#define MESSAGE_NULL_TIMEOUT 800            // Time to send NULL message to keep connecion
#define MESSAGE_APPLY_TIMEOUT 600           // Time to apply arriving message

// Base file names
#define SETTING_FILE "settings5.ini"        // File with all starting data (width, height...)
#define DATA_FILE "data5.dat"               // File with all GFX

// Base game colors
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define GREY {170, 170, 170, 255}

// Macroses
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define SET_MIN(value, min) (value = value < min ? min : value)
#define SET_MAX(value, max) (value = value > max ? max : value)
#define sqr(value) ((value) * (value))
