#include "include.hpp"
#include "define.hpp"
#include "values.hpp"

#include "init.hpp"
#include "initFile.hpp"
#include "dataLoader.hpp"
#include "baseGUI.hpp"
#include "pause.hpp"
#include "entity.hpp"

// Creating main window variables
App app;

// Pause and init settings
LNG_types language;     // Switched languaged from language_types
Uint8 MusicVolume;      // Volume of music
Uint8 EffectsVolume;    // Volume of effects
count drawFPS;          // Max terget FPS to draw

// Global running flags
bool running;            // Flag of main cycle work
bool restart = false;    // Flag of restarting game with other parameters

// Texts variables and constants
#if IMG_count
SDL_Texture* Textures[IMG_count];  // Array of all textures
#endif
#if ANI_count
IMG_Animation* Animations[ANI_count];  // Array of all animations
#endif
#if MUS_count
Mix_Music* Musics[MUS_count];      // Array of all music
#if ARCHIEVE_LOADING
SDL_RWops* MusicsData[MUS_count];  // Array of data for music
#endif
#endif
#if SND_count
Mix_Chunk* Sounds[SND_count];  // Array of all sound effects
#endif
#if FNT_count
Data fontData;  // Data for creating fonts
#endif

// Main function
int main(int argv, char** args){
    initLibraries();  // Initialasing all need libraries
    loadInitFile();   // Load initialasing file file with settings
    createVideo();    // Creating video output system
    
    // Loading data from file
    loadData();

    #if MUS_count
    // Setting volumes of sounds
    Mix_VolumeMusic(MusicVolume);  // Setting volume of music
    Mix_Volume(-1, EffectsVolume);  // Setting volume of effects
    // Infinite playing main game theme
    //Mix_PlayMusic( Musics[MUS_MENU_THEME], -1 );  
    #endif

    // Creating user interface
    setAllText();  // Setting all text
    updateTranslation(language);  // Updating text

    // Main game cycle
    // Selection menu
	selectMenu();

    // Exiting program
    // Stopping playing music
    Mix_PauseMusic();

    // Saving all data to setting file for next starts
    saveInitFile();

    // Clearing static texts
    #if TXT_count
    clearAllText();
    #endif

    // Cleaning all data
    unloadData();

    // Exiting
    deleteVideo();  // Destroying video output
    exitLibraries();  // Exiting all libraries

    // Reloading game
    if(restart){
        restart = false;
        main(argv, args);
    }
	return 0;
}