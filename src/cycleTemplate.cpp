#include "cycleTemplate.hpp"




//
CycleTemplate::CycleTemplate(){
    // Resetting values
    //LMBclick = false;
    selectedBox = 0;

    // Resetting input
    SDL_Event event;
    while( SDL_PollEvent(&event) != 0 );
};

//
CycleTemplate::~CycleTemplate(){

};

//
void CycleTemplate::getInput(){
    SDL_Event event;
    while(true){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                data.running = false;
                return;

            /*case SDL_MOUSEWHEEL:
                // Mouse position on screen
                SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position

                // Checking scroll on sliders
                //if(MusicSlider.scroll(event.wheel.y, mouseX, mouseY));
                //else if(SoundSlider.scroll(event.wheel.y, mouseX, mouseY));
                break;*/

            /*case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){

                };
                break;*/

            case SDL_MOUSEBUTTONDOWN:
                // Getting mouse position
                SDL_GetMouseState(&mouseX, &mouseY);  

                // Getting mouse press 
                if(mouseInput()){
                    // stopping current process if need
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
        data.waitInput();
    }
};

//
Uint8 CycleTemplate::mouseInput(){
    /*if(startOptions[0].in(mouseX, mouseY)){
        return 1;
    }*/

    // None-return
    return 0;
};

//
void CycleTemplate::drawCycle(){
    while (true)
    {
        // Checking for avalible to run
        runMutex.lock();
        runMutex.unlock();

        // Drawing need scene
        draw();

        // Waiting next cycle
        data.waitDraw();
    }
};

//
void CycleTemplate::draw(){
    // Template for draw

}

//
void CycleTemplate::run(){
    // Waiting for input stop
    getInput();

    // Stopping all side threads
    drawThread.detach();
};
