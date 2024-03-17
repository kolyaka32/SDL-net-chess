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


    // Checking correction of all loaded images
    #if CHECK_CORRECTION
    if(!checkCorrection()){
        printf("Wrong count of images");
        exit(ERR_FIL_IMG);
    }
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
    #if !DEBUG
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
    return (count == IMG_count);
};
#endif
