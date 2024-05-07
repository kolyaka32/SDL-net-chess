
#include "base.hpp"

//
GameCycle::GameCycle() : CycleTemplate(MUS_START_NONE){
    endState = END_NONE;
};

//
GameCycle::~GameCycle(){
    
};

//
void GameCycle::getInput(){
    SDL_Event event;
    while(running){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                data.running = false;
                return;

            case SDL_KEYDOWN:
                // Switching between keys
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    // Clearing selection by escape
                    board.resetSelection();
                    break;
                    
                case SDLK_q:
                    // Quiting to menu
                    return;
                }
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
        inputTimer.sleep();
    }
};

//
Uint8 GameCycle::mouseInput(){
    // Pause button
    /*if(settingButton.in(mouseX, mouseY)){
        return 1;
    }*/

    // Checking, if game start
    if(endState <= END_TURN){
        // Clicking on field
        endState = board.click((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE);
    }
    else{
        // Getting buttons clicks
        // Game restart
        if(data.textButtons[BTN_GAME_RESTART].in(mouseX, mouseY)){
            // Restarting game
            endState = END_NONE;

            // Resetting field
            board.reset();

            // Making sound
            data.playSound(SND_RESET);
            return 0;
        }
        // Going to menu
        else if(data.textButtons[BTN_GAME_MENU].in(mouseX, mouseY)){
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

    // Draw surround letters
    letters.blit();

    // Drawing player state
    data.texts[TXT_GAME_TURN_FIRST + board.currentTurn()].blit();

    // Bliting game state, if need
    if(endState > END_TURN){
        // Bliting end background
        endBackplate.blit();

        // Bliting text with end state
        switch (endState)
        {
        case END_WIN:
            data.texts[TXT_END_WIN_1].blit();
            break;
        
        case END_LOOSE:
            data.texts[TXT_END_WIN_2].blit();
            break;
        
        case END_NOBODY:
            data.texts[TXT_END_NOBODY].blit();
            break;
        }

        // Blitting buttons
        data.textButtons[BTN_GAME_RESTART].blit();
        data.textButtons[BTN_GAME_MENU].blit();
    }

    // Bliting all to screen
    data.render();
};
