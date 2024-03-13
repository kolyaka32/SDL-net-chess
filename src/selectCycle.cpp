#include "include.hpp"
#include <thread>
#include "data.hpp"
#include "selectCycle.hpp"


// Selectable GUI object
enum {
    BOX_NORMAL,
    BOX_OPTIONS,
    BOX_SINGLE,
    BOX_TWO_PLAYERS,
    BOX_SERVER,
    BOX_CLIENT
} SELECTED_BOX_TYPES;



SelectCycle::SelectCycle(){
    running = true;
    stop = false;
    LMBclick = false;
    selectedBox = BOX_NORMAL;
};

SelectCycle::~SelectCycle(){

};

void SelectCycle::getInput(){

    SDL_Event event;
    while(running){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                data.running = false;
                running = false;  // Exit from program
                break;

            case SDL_MOUSEWHEEL:
                // Mouse position on screen
                SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position

                // Checking scroll on sliders
                //if(MusicSlider.scroll(event.wheel.y, mouseX, mouseY));
                //else if(SoundSlider.scroll(event.wheel.y, mouseX, mouseY));
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){

                };
                break;

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position
                mouseInput();
                break;

            case SDL_MOUSEBUTTONUP:
                LMBclick = false; 
                selectedBox = BOX_NORMAL;
                break;
            }
        }
        // Waiting next cycle
        data.waitInput();
    }
};


void SelectCycle::mouseInput(){

};


void SelectCycle::drawing(){
    while (running)
    {
        // Bliting background
        SDL_RenderClear(data.renderer);

        // Blitting buttons
        // Start variants
        for(Uint8 i=0; i < optionsCount; ++i){
            startOptions[i].blit();
        };
        // Settings menu
        settingButton.blit();

        // Bliting all to screen
        data.render();

        // Waiting next cycle
        data.waitDraw();
    }
    
};


void SelectCycle::run(){

    // Starting new threads
    std::thread inputThread(getInput);
    std::thread drawThread(drawing);

    // Waiting, while one is stop
    inputThread.join();
    running = false;
    drawThread.detach();
};
