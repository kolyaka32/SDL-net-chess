#include "include.hpp"
#include "values.hpp"
#include "define.hpp"
#include "pause.hpp"
#include "gameSingle.hpp"

static bool twoPlayers;  // Flag of mode with two players to show text of 1/2 player instead of you

Uint8 fieldWidth;        // Width and height of field
Uint8 winWidth;          // Width, which need for win
Uint8 queue;             // Modifictor to change picture of current player (0 for cross, 1 for circle)
Uint8 player;            // Number of player, which selected

Field field;             // Main game field

// Menu for waiting to restart or go to menu
inline void stopMenu(){
    // Creating buttons
    GUI::Button stopButtons[] = {
        {0.5, 0.7, IMG_MENU_BUTTON, texts + TXT_STOP_RESTART},
        {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU}
    };
    for(Uint8 i=0; i < 2; ++i){
        stopButtons[i].init();
    }

    // Starting Internal loop of waiting for restart/go to menu
    bool waiting = true;
    start = true;
    SDL_Event event;
    while(waiting){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                waiting = false;
                return;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                if(stopButtons[0].in(MouseX, MouseY)){
                    // Restarting round
                    field.reset();
                    start = true;
                    waiting = false;
                }
                else if(stopButtons[1].in(MouseX, MouseY)){
                    // Going to menu
                    runGame = false;
                    waiting = false;
                }
                break;
            }
        }
        // Drawing
        SDL_RenderClear(app.renderer);

        // Draw game stop reason
        if(gameState < END_NOBODY && twoPlayers){
            texts[TXT_STOP_WIN_1 - 1 + gameState].blit();
        }
        else{
            texts[TXT_STOP_WIN - 1 + gameState].blit();
        }
        
        // Showing buttons
        for(Uint8 i=0; i < 2; ++i){
            stopButtons[i].blit();
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer);

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    // Clearing data
    gameState = END_NONE;
    player = 0;
}

// Singleplayer mode of game
void singleMainCycle(){
    // Creating start buttons
    GUI::Button queueButton[] = {
        {0.25, 0.5, IMG_GREEN_CROSS},
        {0.75, 0.5, IMG_GREEN_CIRCLE}
    };

    for(Uint8 i=0; i < 2; ++i){
        queueButton[i].init();
    }

    // Resetting field
    field.reset();
    player = 0;

    // Variables for loop
    SDL_Event event;
    runGame = true;
    start = true;

    // Starting main game loop
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return;

            case SDL_KEYDOWN:
                // Checking for restart key
                switch (event.key.keysym.sym)
                {
                case SDLK_r:
                    // Skipping game
                    gameState = END_SKIP;
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                if(start){
                    if(queueButton[0].in(MouseX, MouseY)){
                        // Activation cross - moving first
                        queue = 0;
                        start = false;
                    }
                    else if(queueButton[1].in(MouseX, MouseY)){
                        // Activating circle - moving second
                        queue = 1;
                        // First move of AI
                        field.AImove();
                        start = false;
                    }
                }
                else {
                    field.clickSingle(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR));
                }
                break;
            }
        }

        // Checking end of game
        if(gameState){
            stopMenu();
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Showing game chose
        if(start){
            // Showing text for Activation
            texts[TXT_START_SELECT].blit();
            // Showing buttons for chose
            for(Uint8 i=0; i < 2; ++i){
                queueButton[i].blit();
            }
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
}

//
void twoMainCycle(){
    // Resetting field
    field.reset();
    //single = false;
    queue = 0;

    // Variables for loop
    SDL_Event event;
    runGame = true;
    twoPlayers = true;

    // Starting loop for waiting for start
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return;

            case SDL_KEYDOWN:
                // Checking for restart key
                switch (event.key.keysym.sym)
                {
                case SDLK_r:
                    // Skipping game
                    gameState = END_SKIP;
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                field.clickTwo(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR));
                break;
            }
        }

        // Checking end of game
        if(gameState){
            stopMenu();
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    twoPlayers = false;
}
