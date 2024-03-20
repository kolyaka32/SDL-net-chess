#include "selectCycle.hpp"
#include "pauseCycle.hpp"


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

};

//
SelectCycle::~SelectCycle(){

};

//
Uint8 SelectCycle::mouseInput(){
    if(settingButton.in(mouseX, mouseY)){
        // Stopping all current threads
        runMutex.lock();

        // Launching new pause cycle
        PauseCycle pauseCycle;
        pauseCycle.run();

        // Unlocking all threads
        runMutex.unlock();
    }
    else if(startOptions[0].in(mouseX, mouseY)){

    }
    else if(startOptions[1].in(mouseX, mouseY)){

    }
    else if(startOptions[2].in(mouseX, mouseY)){

    }
    else if(startOptions[3].in(mouseX, mouseY)){

    }

    // None-return
    return 0;
};

//
void SelectCycle::draw(){
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
};
