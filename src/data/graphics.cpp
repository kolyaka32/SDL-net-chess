/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "graphics.hpp"
#include "../workCodes.hpp"


// Library for work with any images
// Initialasing SDL graphic library
GraphicsLibrary::GraphicsLibrary() {
    // Initializing image library
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        #if CHECK_CORRECTION
        SDL_Log("Couldn't initialize image library: %s\n", IMG_GetError());
        exit(ERR_SDL_IMG);
        #endif
    }
}

// Closing SDL hraphic library
GraphicsLibrary::~GraphicsLibrary() {
    IMG_Quit();
}


// Loading all textures
Textures::Textures() {
    // Resetting list of textures
    #if CHECK_CORRECTION
    memset(textures, 0, IMG_count * sizeof(textures[0]));
    #endif

    // Loading all images
    // loadTexture(".png", IMG_);  // Template

    // Graphic interface sprites
    loadTexture("GUI/esc_button.png", IMG_GUI_PAUSE_BUTTON);
    loadTexture("GUI/slider_button.png", IMG_GUI_SLIDER_BUTTON);
    loadTexture("GUI/slider_line.png", IMG_GUI_SLIDER_LINE);
    loadTexture("GUI/type_box.png", IMG_GUI_TYPE_BOX);

    // Base flags in settings
    loadTexture("GUI/Flag_USA.png", IMG_GUI_FLAG_USA);
    loadTexture("GUI/Flag_RUS.png", IMG_GUI_FLAG_RUS);
    loadTexture("GUI/Flag_GER.png", IMG_GUI_FLAG_GER);
    loadTexture("GUI/Flag_BEL.png", IMG_GUI_FLAG_BEL);

    // Main game part
    // Game field
    loadTexture("chess-pack-1/chessboard.png", IMG_GAME_FIELD);

    // Game figures
    // White figures
    loadTexture("chess-pack-1/w-pawn.png", IMG_GAME_WHITE_PAWN);
    loadTexture("chess-pack-1/w-bishop.png", IMG_GAME_WHITE_BISHOP);
    loadTexture("chess-pack-1/w-rook.png", IMG_GAME_WHITE_ROOK);
    loadTexture("chess-pack-1/w-knight.png", IMG_GAME_WHITE_KNIGHT);
    loadTexture("chess-pack-1/w-queen.png", IMG_GAME_WHITE_QUEEN);
    loadTexture("chess-pack-1/w-king.png", IMG_GAME_WHITE_KING);

    // Black figures
    loadTexture("chess-pack-1/b-pawn.png", IMG_GAME_BLACK_PAWN);
    loadTexture("chess-pack-1/b-bishop.png", IMG_GAME_BLACK_BISHOP);
    loadTexture("chess-pack-1/b-rook.png", IMG_GAME_BLACK_ROOK);
    loadTexture("chess-pack-1/b-knight.png", IMG_GAME_BLACK_KNIGHT);
    loadTexture("chess-pack-1/b-queen.png", IMG_GAME_BLACK_QUEEN);
    loadTexture("chess-pack-1/b-king.png", IMG_GAME_BLACK_KING);

    // Point, where figure can go
    loadTexture("chess-pack-1/point.png", IMG_GAME_POINT_MOVE_TO);

    // Resetting color for figures
    for (Uint8 i = IMG_GAME_WHITE_PAWN; i <= IMG_GAME_BLACK_KING; ++i) {
        SDL_SetTextureColorMod(textures[i], 0, 0, 0);
    }

    // Checking correction of all loaded images
    #if CHECK_CORRECTION
    checkCorrection();
    #endif
}

// Clearing all textures after work
Textures::~Textures() {
    for (Uint8 i = 0; i < IMG_count; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

// Loading texture with need name
void Textures::loadTexture(const std::string _name, const IMG_names _index) {
    // Getting selected picture data
    SDL_RWops *tempRW = loadObject("img/" + _name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if (!tempRW) {
        SDL_Log("Error with loading image file '%s' at %u.", _name, _index);
        throw "Error with loading image file";
        exit(ERR_FIL_IMG);
    }
    #endif

    // Creating surface from data
    SDL_Surface *tempSurface = IMG_Load_RW(tempRW, 0);

    // Freeing picture data
    #if ARCHIEVE_LOADING
    free(tempRW->hidden.mem.base);
    #endif
    SDL_RWclose(tempRW);

    // Creating texture from surface and setting to it place
    textures[_index] = SDL_CreateTextureFromSurface(renderer, tempSurface);

    // Clearing data
    SDL_FreeSurface(tempSurface);

    // Checking correction of loaded texture
    #if CHECK_CORRECTION
    if (textures[_index] == nullptr) {
        SDL_Log("Error with loading image file '%s' at %u.", _name, _index);
        exit(ERR_FIL_IMG);
    }
    #endif
}

// Checking correction of loaded textures
#if CHECK_CORRECTION
void Textures::checkCorrection() {
    // Checking, if all images exist
    for (Uint8 i = 0; i < IMG_count; ++i) {
        if (textures[i] == NULL) {
            SDL_Log("Wrong texture at %u.", i);
            exit(ERR_FIL_IMG);
        }
    }
}
#endif
