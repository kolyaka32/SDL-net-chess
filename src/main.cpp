#include "include.hpp"
#include "define.hpp"
#include "GUI/baseGUI.hpp"
#include "process.hpp"

// Pause and init settings
//Uint8 language;         // Switched languaged from language_types
//Uint8 MusicVolume;      // Volume of music
//Uint8 EffectsVolume;    // Volume of effects
//count drawFPS;          // Max terget FPS to draw

// Global running flags
bool running;            // Flag of main cycle work
bool restart = false;    // Flag of restarting game with other parameters

// Main function
int main(int argv, char** args){

    #if MUS_count
    // Setting volumes of sounds
    //Mix_VolumeMusic(MusicVolume);  // Setting volume of music
    //Mix_Volume(-1, EffectsVolume);  // Setting volume of effects
    // Infinite playing main game theme
    //Mix_PlayMusic( Musics[MUS_MENU_THEME], -1 );  
    #endif

    // Starting main process
    Process process;
    process.run();

    // Creating user interface
    //updateTranslation(language);  // Updating text

    // Main game cycle
    // Selection menu
	//selectMenu();

    // Exiting program
    // Stopping playing music
    //Mix_PauseMusic();


    // Reloading game
    if(restart){
        restart = false;
        main(argv, args);
    }
	return 0;
}