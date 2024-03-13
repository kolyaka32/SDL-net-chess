#include "include.hpp"
#include "define.hpp"
#include "process.hpp"
#include "workCodes.hpp"

// Global running flags
bool running;            // Flag of main cycle work
bool restart = false;    // Flag of restarting game with other parameters

// Main process data
Data data;

// Main function
int main(int argv, char **args){

    // Starting main process
    //Process process;
    //process.run();

    // Showing base picture
    SDL_RenderCopy(data.renderer, data.textures[IMG_GUI_FLAG_RUS], NULL, NULL);

    // Rendering
    data.render();

    // Test program timer
    SDL_Delay(2000);

    // Reloading game
    if(restart){
        restart = false;
        return main(argv, args);
    };

    // Finishing main process
	return NOR_WOR;
}