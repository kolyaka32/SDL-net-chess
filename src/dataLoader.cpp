#include "include.hpp"
#include "define.hpp"
#include "values.hpp"

#include "init.hpp"
#include "dataLoader.hpp"

typedef Uint8 counter;  // Type of data for count number of loaded objects

// Functions of loading need outside data
#if ARCHIEVE_LOADING
// Functions for loading data from archieve
// Loading need library
#include "zip.h"

// Arcieve local structs
static zip_t* archive;  // Archive with all data

// Function of open archive and setting base password
static inline zip_t* openarchive(){
    // Open archive with need name
    archive = zip_open(DATA_FILE, ZIP_RDONLY, NULL);

    #if PASSWORD
    zip_set_default_password(archive, PASSWORD);
    #endif

    // Returning archive for checking correction
    return archive;
};

// Function of getting data of archive file
static inline SDL_RWops* dataFromarchive(const char* name){
    // Openning need file
    zip_file_t* file = zip_fopen_encrypted(archive, name, 0, PASSWORD);
    
    zip_stat_t st;
	zip_stat(archive, name, 0, &st);  // Getting data of current file
    // Checking correction of file
    if(st.size == 0){  
        return NULL;
    }

    // Copping data to buffer
    char* buffer = (char*)malloc(sizeof(char*)*st.size);
    zip_fread(file, buffer, st.size);
    zip_fclose(file);
    // Creating SDL-based structure with data
    SDL_RWops* tempRW = SDL_RWFromMem(buffer, st.size);

    // Returning created data structure
    return tempRW;
};

// Icone functions
#if ICO_count
// Function of loading game icone
inline unsigned loadIcone(const char* name){
    // Getting icone data
    SDL_RWops* tempRW = dataFromarchive(name);

    // Setting window icone
    SDL_Surface* iconeImage = IMG_LoadICO_RW(tempRW);
    if(iconeImage == NULL){  // Checking creating image
        return 0;  // Returning 0 as error with loading
    }
    SDL_RWclose(tempRW);
    SDL_SetWindowIcon(app.window, iconeImage);
    SDL_FreeSurface(iconeImage);
    return ICO_count;  // Returning correction of loading
};
#endif

// Images functions
#if IMG_count
static counter loadedImages;
// Functions of loading selected image file
static void loadPicture(const char* name, IMG_names number){
    // Getting selected picture data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating texture from data
    Textures[number] = SDL_CreateTextureFromSurface(app.renderer, IMG_LoadPNG_RW(tempRW));
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Textures[number] != NULL){
        loadedImages++;
    };
};
#endif

// Animations functions
#if ANI_count
static counter loadedAnimations;
// Function of loading selected GIF animation
static void loadAnimation(const char* name, ANI_names number){
    // Getting selected animation data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating animation from data
    Animations[number] = IMG_LoadAnimation_RW(tempRW, 0);
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Animations[number] != NULL){
        loadedAnimations++;
    };
};
#endif

// Musics functions
#if MUS_count
static counter loadedMusics;
// Function of loading selected music file
static void loadMusic(const char* name, MUS_names number){
    // Getting selected music track data
    MusicsData[number] = dataFromarchive(name);
    // Creating music track from data
    Musics[number] = Mix_LoadMUS_RW(MusicsData[number], 0);

    // Checking correction of loaded file
    if(Musics[number] != NULL){
        loadedMusics++;
    };
};
#endif

// Sounds functions
#if SND_count
static counter loadedSounds;
// Function of loading selected sound
static void loadSound(const char* name, SND_names number){
    // Getting selected sound data
    SDL_RWops* tempRW = dataFromarchive(name);
    // Creating sound from data
    Sounds[number] = Mix_LoadWAV_RW(tempRW, 0);
    SDL_RWclose(tempRW);

    // Checking correction of loaded file
    if(Sounds[number] != NULL){
        loadedSounds++;
    };
};
#endif

// Function of loading font
#if FNT_count
static unsigned loadFont(const char* name){
    // Openning font file
    zip_file_t* file = zip_fopen_encrypted(archive, name, 0, PASSWORD);
    
    zip_stat_t st;
	zip_stat(archive, name, 0, &st);  // Getting data from file

    // Checking correction of file
    if(st.size == 0){  
        return 0;
    }

    // Copping data to buffer
    fontData.data = (char*)malloc(sizeof(char) * st.size);
    fontData.size = st.size;
    zip_fread(file, fontData.data, fontData.size);
    zip_fclose(file);

    // Checking correction
    return FNT_count;
};
#endif
#else
// Trying loading data from folder for testing

#if ICO_count
// Function of loading game icone
inline unsigned loadIcone(const char* name){
    // Getting icone data
    SDL_Surface* iconeImage = IMG_Load(name);
    // Setting window icone
    SDL_SetWindowIcon(app.window, iconeImage);
    SDL_FreeSurface(iconeImage);
    return ICO_count;  // Returning correction of loading
};
#endif

// Images functions
#if IMG_count
static counter loadedImages;
// Functions of loading selected image file
static void loadPicture(const char* name, IMG_names number){
    // Loading texture from data
    Textures[number] = IMG_LoadTexture(app.renderer, name);

    // Checking correction of loaded file
    if(Textures[number] != NULL){
        loadedImages++;
    };
};
#endif

// Animations functions
#if ANI_count
static counter loadedAnimations;
// Function of loading selected GIF animation
static void loadAnimation(const char* name, ANI_names number){
    // Creating animation from data
    Animations[number] = IMG_LoadAnimation(name);

    // Checking correction of loaded file
    if(Animations[number] != NULL){
        loadedAnimations++;
    };
};
#endif

// Musics functions
#if MUS_count
static counter loadedMusics;
// Function of loading selected music file
static void loadMusic(const char* name, MUS_names number){
    // Creating music track from data
    Musics[number] = Mix_LoadMUS(name);

    // Checking correction of loaded file
    if(Musics[number] != NULL){
        loadedMusics++;
    };
};
#endif

// Sounds functions
#if SND_count
static counter loadedSounds;
// Function of loading selected sound
static void loadSound(const char* name, SND_names number){
    // Creating sound from data
    Sounds[number] = Mix_LoadWAV(name);

    // Checking correction of loaded file
    if(Sounds[number] != NULL){
        loadedSounds++;
    };
};
#endif

// Function of loading font
#if FNT_count
static unsigned loadFont(const char* name){
    // Openning font file
    SDL_RWops* fontFile = SDL_RWFromFile(name, "r");

    // Getting file size for creating memory for it
    fontData.size = SDL_RWsize(fontFile);

    // Checking correction of file
    if(!fontData.size){
        return 0;
    }

    fontData.data = (char*)malloc(sizeof(char) * fontData.size);
    SDL_RWread(fontFile, fontData.data, fontData.size, 1);

    // Closing font file
    SDL_RWclose(fontFile);

    // Checking correction
    return FNT_count;
};
#endif
#endif

// Images functions
#if IMG_count
// Loading all images
inline unsigned loadAllImages(){
    loadedImages = 0;  // Resseting counter
    //loadPicture("img/.png", IMG_);

    loadPicture("img/esc_button.png", IMG_MENU_PAUSE);
    loadPicture("img/slider_button.png", IMG_MENU_SCROLLER_BUTTON);
    loadPicture("img/slider_line.png", IMG_MENU_SCROLLER_LINE);
    loadPicture("img/button.png", IMG_MENU_BUTTON);
    loadPicture("img/type_box.png", IMG_MENU_TYPE_BOX);

    loadPicture("img/Flag_USA.png", IMG_FLAG_USA);
    loadPicture("img/Flag_RUS.png", IMG_FLAG_RUS);

    loadPicture("img/green_circle.png", IMG_GREEN_CIRCLE);
    loadPicture("img/green_cross.png", IMG_GREEN_CROSS);
    loadPicture("img/red_circle.png", IMG_RED_CIRCLE);
    loadPicture("img/red_cross.png", IMG_RED_CROSS);

    loadPicture("img/cell.png", IMG_CELL);


    // Returning numbers of loaded files
    return loadedImages;
};
#endif

// Animations functions
#if ANI_count
// Loading all animations
inline unsigned loadAllAnimations(){
    loadedAnimations = 0;  // Resseting counter
    //loadAnimation("ani/.gif", ANI_);

    // Returning numbers of loaded files
    return loadedAnimations;
};
#endif

// Musics functions
#if MUS_count
// Loading all music tracks
static unsigned loadAllMusic(){
    loadedMusics = 0;  // Resseting counter
    //loadMusic("mus/.mp3", MUS_);
    //loadMusic("mus/main_theme.mp3", MUS_MAIN_THEME);
    //loadMusic("mus/menu_theme.mp3", MUS_MENU_THEME);

    // Returning numbers of loaded files
    return loadedMusics;
};
#endif

// Sounds functions
#if SND_count
// Loading all sounds
static unsigned loadAllSounds(){
    loadedSounds = 0;  // Resseting counter
    //loadSound("snd/.wav", SND_);
    //loadSound("snd/click.wav", SND_CLICK);
    //loadSound("snd/flagSet.wav", SND_FLAG_SET);
    //loadSound("snd/loose.wav", SND_LOOSE);
    //loadSound("snd/win.wav", SND_WIN);

    // Returning numbers of loaded files
    return loadedSounds;
};
#endif

// Main data loading function
void loadData(){
    // Opening archive
    #if ARCHIEVE_LOADING
    if(openarchive() == NULL){
        printf("Can't load arcieve");
        exit(ERR_FIL_OPN);
    } 
    #endif

    // Loading data from archive
    #if ICO_count
    if(loadIcone("img/Game.ico") != ICO_count){
        printf("Can't load game icone");
        exit(ERR_FIL_ICO);
    }
    #endif
    #if IMG_count
    if(loadAllImages() != IMG_count){
        printf("Wrong count of images");
        exit(ERR_FIL_IMG);
    }
    #endif
    #if ANI_count
    if(loadAllAnimations() != ANI_count){
        printf("Wrong count of animations");
        exit(ERR_FIL_ANI);
    }
    #endif
    #if MUS_count
    if(loadAllMusic() != MUS_count){
        printf("Wrong count of music");
        exit(ERR_FIL_MUS);
    }
    #endif
    #if SND_count
    if(loadAllSounds() != SND_count){
        printf("Wrong count of sounds");
        exit(ERR_FIL_SND);
    }
    #endif
    #if ICO_count
    if(loadFont("fnt/Arial.ttf") != FNT_count){
        printf("Can't load font");
        exit(ERR_FIL_FNT);
    }
    #endif

    #if ARCHIEVE_LOADING
    // Closing archive
    zip_close(archive);
    #endif
}

// Function of clearing all temporary data, loaded from arcieve
void unloadData(){
    // Unloading data in reverce form from loading

    // Deliting font data
    #if FNT_count
    free(fontData.data);
    #endif
    // Unloading sound effects
    #if SND_count
    for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(Sounds[i]);
    }
    #endif
    // Unloading music effects and data
    #if MUS_count
    for(int i=0; i < MUS_count; ++i){
        Mix_FreeMusic(Musics[i]);
        #if ARCHIEVE_LOADING
        SDL_RWclose(MusicsData[i]);
        #endif
    }
    #endif
    // Unloading gif animations
    #if ANI_count
    for(int i=0; i < ANI_count; ++i){
        IMG_FreeAnimation(Animations[i]);
    }
    #endif
    // Unloading images
    #if IMG_count
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        //Textures[i] = NULL;
    }
    #endif
};
