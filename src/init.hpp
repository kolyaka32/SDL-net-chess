
#pragma once

// Function of initialasing all libraries
void initLibraries();

// Function of creating window and renderer for outputing image
void createVideo();

// Function of deliting window and renders
void deleteVideo();

// Function of closing all outside libraries and files
void exitLibraries();

// Work codes
// Normal work
#define NOR_NOR 0x00000  // Normal work of program without any problems

// Errors codes
// Error codes of libraries
#define ERR_SDL_OTH 0x00010  // error with other sdl library
#define ERR_SDL_SDL 0x00011  // error with main sdl library
#define ERR_SDL_IMG 0x00012  // error with image sdl library
#define ERR_SDL_SND 0x00013  // error with sound sdl library
#define ERR_SDL_FFT 0x00014  // error with font sdl library
#define ERR_SDL_NET 0x00015  // error with network sdl liblary
#define ERR_ZIP_LIB 0x00016  // error with ziplib library

// Global initialisations
#define ERR_INI_OTH 0x00020  // error with other initialisation
#define ERR_INI_WIN 0x00021  // error with window creation
#define ERR_INI_REN 0x00022  // error with render creation
#define ERR_INI_SND 0x00023  // error with audio initialisation

// Error codes of loading file
#define ERR_FIL_OTH 0x00030  // error with other file context
#define ERR_FIL_OPN 0x00031  // error with file openning
#define ERR_FIL_ICO 0x00032  // error with file number of icones
#define ERR_FIL_IMG 0x00033  // error with file number of images
#define ERR_FIL_ANI 0x00034  // error with file number of animations
#define ERR_FIL_MUS 0x00035  // error with file number of musics
#define ERR_FIL_SND 0x00036  // error with file number of effects
#define ERR_FIL_FNT 0x00037  // error with file font
