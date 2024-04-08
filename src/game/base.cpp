
#include "base.hpp"


//
GameCycle::GameCycle() : CycleTemplate(MUS_MAIN_THEME){

};

//
GameCycle::~GameCycle(){

};

//
void GameCycle::getInput(){
    SDL_Event event;
    while(true){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                data.running = false;
                return;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    return;
                };
                break;

            case SDL_MOUSEBUTTONDOWN:
                // Getting mouse position
                SDL_GetMouseState(&mouseX, &mouseY);

                // Getting mouse press
                if(mouseInput()){
                    return;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                //LMBclick = false;
                selectedBox = 0;
                break;
            }
        }
        
        // Waiting next cycle
        data.waitDraw();
    }
};

//
Uint8 GameCycle::mouseInput(){
    //
    Uint8 newLanguage = data.language;

    //
    /*if(settingButton.in(mouseX, mouseY)){
        return 1;
    }*/

    // Clicking on field
    board.click(mouseX, mouseY);

    // None-return
    return 0;
};

//
void GameCycle::draw() const{
    // Bliting field
    board.blit();

    // Bliting title
    //data.texts[TXT_PAUSE_TITLE].blit();


    // Bliting all to screen
    data.render();
};
