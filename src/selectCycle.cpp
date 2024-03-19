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



//
SelectCycle::SelectCycle(){
    // Resetting values
    LMBclick = false;
    selectedBox = BOX_NORMAL;
};

//
SelectCycle::~SelectCycle(){

};

//
void SelectCycle::getInput(){
    SDL_Event event;
    while(true){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                data.running = false;
                //stop.lock();
                //running = false;  // Exit from program
                return;

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
                // Getting mouse position
                SDL_GetMouseState(&mouseX, &mouseY);  

                // Getting mouse press 
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

//
void SelectCycle::mouseInput(){
    if(startOptions[0].in(mouseX, mouseY)){

    }
    else if(startOptions[1].in(mouseX, mouseY)){

    }
    else if(startOptions[2].in(mouseX, mouseY)){

    }
    else if(startOptions[3].in(mouseX, mouseY)){

    }
    else if(settingButton.in(mouseX, mouseY)){

    }
};

//
void SelectCycle::drawing(){
    while (true)
    {
        // Bliting background
        SDL_RenderClear(data.renderer);

        // Bliting title
        data.texts[TXT_SELECT_TITLE].blit();

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

//
void SelectCycle::run(){
    // Waiting for input stop
    getInput();

    // Stopping all side threads
    drawThread.detach();
};
