#include "graphics.hpp"
#include "../workCodes.hpp"


// Library for work with any images
// Initialasing SDL graphic library
GraphicsLibrary::GraphicsLibrary(){
    // Initializing image library
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        #if CHECK_CORRECTION
        printf("Couldn't initialize image library: %s\n", IMG_GetError());
        exit(ERR_SDL_IMG);
        #endif
    }
}

// Closing SDL hraphic library
GraphicsLibrary::~GraphicsLibrary(){
    IMG_Quit();
}


// Loading all textures
Textures::Textures(){
    // Resetting list of textures
    #if CHECK_CORRECTION
    memset(textures, 0, IMG_count * sizeof(textures[0]));
    #endif

    // Loading all images
    //loadTexture("img/.png", IMG_);  // Template

    // Graphic interface sprites
    loadTexture("img/GUI/esc_button.png", IMG_GUI_PAUSE_BUTTON);
    loadTexture("img/GUI/slider_button.png", IMG_GUI_SLIDER_BUTTON);
    loadTexture("img/GUI/slider_line.png", IMG_GUI_SLIDER_LINE);
    loadTexture("img/GUI/button.png", IMG_GUI_BASE_BUTTON);
    loadTexture("img/GUI/type_box.png",IMG_GUI_TYPE_BOX);

    // Base flags in settings
    loadTexture("img/GUI/Flag_USA.png", IMG_GUI_FLAG_USA);
    loadTexture("img/GUI/Flag_RUS.png", IMG_GUI_FLAG_RUS);
    loadTexture("img/GUI/Flag_GER.png", IMG_GUI_FLAG_GER);
    loadTexture("img/GUI/Flag_BEL.png", IMG_GUI_FLAG_BEL);

    // Main game part
    // Game field
    loadTexture("img/chess-pack-1/chessboard.png", IMG_GAME_FIELD);

    // Game figures
    // White figures
    loadTexture("img/chess-pack-1/w-pawn.png", IMG_GAME_WHITE_PAWN);
    loadTexture("img/chess-pack-1/w-bishop.png", IMG_GAME_WHITE_BISHOP);
    loadTexture("img/chess-pack-1/w-rook.png", IMG_GAME_WHITE_ROOK);
    loadTexture("img/chess-pack-1/w-knight.png", IMG_GAME_WHITE_KNIGHT);
    loadTexture("img/chess-pack-1/w-queen.png", IMG_GAME_WHITE_QUEEN);
    loadTexture("img/chess-pack-1/w-king.png", IMG_GAME_WHITE_KING);

    // Black figures
    loadTexture("img/chess-pack-1/b-pawn.png", IMG_GAME_BLACK_PAWN);
    loadTexture("img/chess-pack-1/b-bishop.png", IMG_GAME_BLACK_BISHOP);
    loadTexture("img/chess-pack-1/b-rook.png", IMG_GAME_BLACK_ROOK);
    loadTexture("img/chess-pack-1/b-knight.png", IMG_GAME_BLACK_KNIGHT);
    loadTexture("img/chess-pack-1/b-queen.png", IMG_GAME_BLACK_QUEEN);
    loadTexture("img/chess-pack-1/b-king.png", IMG_GAME_BLACK_KING);

    // Point, where figure can go
    loadTexture("img/chess-pack-1/point.png", IMG_GAME_POINT_MOVE_TO);


    // Checking correction of all loaded images
    #if CHECK_CORRECTION
    checkCorrection();
    #endif
};

// Clearing all textures after work
Textures::~Textures(){
    for(Uint8 i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(textures[i]);
    }
}

// Loading texture with need name
void Textures::loadTexture(const char *_name, IMG_names _index){
    // Getting selected picture data
    SDL_RWops *tempRW = loadObject(_name);

    // Checking correction of loaded data
    #if CHECK_CORRECTION
    if(!tempRW){
        printf("Error with loading image file '%s' at %u.", _name, _index);
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
};

// Checking correction of loaded textures
#if CHECK_CORRECTION
void Textures::checkCorrection(){
    // Checking, if all images exist
    for(Uint8 i = 0; i < IMG_count; ++i){
        if(textures[i] == NULL){
            printf("Wrong texture at %u.", i);
            exit(ERR_FIL_IMG);
        }
    }
};
#endif
