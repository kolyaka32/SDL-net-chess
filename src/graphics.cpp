#include "include.hpp"
#include "graphics.hpp"
#include "workCodes.hpp"


GraphicsLibrary::GraphicsLibrary(){
    // Initializing image library
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Couldn't initialize image library: %s\n", IMG_GetError());
        exit(ERR_SDL_IMG);
    }
}

GraphicsLibrary::~GraphicsLibrary(){
    // Closing image library
    IMG_Quit();
}


//
Textures::Textures(){
    // Resetting list of textures
    memset(textures, 0, IMG_count);

    // Loading all images
    //loadTexture("img/.png", IMG_);  // Template

    loadTexture("img/esc_button.png", IMG_MENU_PAUSE);
    loadTexture("img/slider_button.png", IMG_MENU_SCROLLER_BUTTON);
    loadTexture("img/slider_line.png", IMG_MENU_SCROLLER_LINE);
    loadTexture("img/button.png", IMG_MENU_BUTTON);
    loadTexture("img/type_box.png", IMG_MENU_TYPE_BOX);

    loadTexture("img/Flag_USA.png", IMG_FLAG_USA);
    loadTexture("img/Flag_RUS.png", IMG_FLAG_RUS);

    loadTexture("img/green_circle.png", IMG_GREEN_CIRCLE);
    loadTexture("img/green_cross.png", IMG_GREEN_CROSS);
    loadTexture("img/red_circle.png", IMG_RED_CIRCLE);
    loadTexture("img/red_cross.png", IMG_RED_CROSS);

    loadTexture("img/cell.png", IMG_CELL);

    // Checking correction of all loaded images
    if(checkCorrection()){
        printf("Wrong count of images");
        exit(ERR_FIL_IMG);
    }
};

//
Textures::~Textures(){
    // Clearing all textures after work
    for(Uint8 i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(textures[i]);
    }
}

//
void Textures::loadTexture(const char *name, IMG_names index){
    // Getting selected picture data
    SDL_RWops *tempRW = loadObject(name);

    // Checking correction of loaded data
    if(!tempRW){
        printf("Error with loading image file '%s' at %u.", name, index);
        exit(ERR_FIL_IMG);
    }

    // Creating surface from data
    SDL_Surface *tempSurface = IMG_LoadPNG_RW(tempRW);

    // Creating texture from surface and setting to it place
    textures[index] = SDL_CreateTextureFromSurface(renderer, tempSurface);

    // Clearing data
    SDL_FreeSurface(tempSurface);
    SDL_RWclose(tempRW);
};

// 
bool Textures::checkCorrection(){
    // Setting counter
    Uint8 count = 0;

    // Checking, if all images exist
    for(Uint8 i = 0; i < IMG_count; ++i){
        if(textures[i]){
            count++;
        }
    }

    // Returing correction of loaded number
    return count == IMG_count;
};
