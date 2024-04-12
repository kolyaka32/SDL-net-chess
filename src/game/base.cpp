
#include "base.hpp"

//
GameCycle::GameCycle() : CycleTemplate(MUS_MAIN_THEME){
    endState = END_NONE;
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
    // Pause button
    /*if(settingButton.in(mouseX, mouseY)){
        return 1;
    }*/

    // Clicking on field if possible
    if(endState == END_NONE){
        // Clicking on field
        endState = board.click(mouseX / CELL_SIDE, mouseY / CELL_SIDE);
    }
    else{
        // Getting buttons clicks
        // Game restart
        if(restartButton.in(mouseX, mouseY)){
            // Restarting game
            endState = END_NONE;

            // Resetting field
            board.reset();

            // Making sound
            data.playSound(SND_RESET);
            return 0;
        }
        // Going to menu
        else if(menuButton.in(mouseX, mouseY)){
            return 1;
        }
    }

    // None-return
    return 0;
};

//
void GameCycle::draw() const{
    // Bliting field
    board.blit();

    // Bliting game state, if need
    if(endState != END_NONE){
        // Bliting end background
        endBackplate.blit();

        // Bliting text
        data.texts[TXT_END_WIN + endState].blit();

        // Blitting buttons
        restartButton.blit();
        menuButton.blit();
    }

    // Bliting all to screen
    data.render();
};
