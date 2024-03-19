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

};

//
SelectCycle::~SelectCycle(){

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
