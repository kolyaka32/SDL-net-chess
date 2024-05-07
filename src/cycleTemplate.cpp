#include "cycleTemplate.hpp"



//
CycleTemplate::CycleTemplate(MUS_names _music) : music(_music){
    // Start locking for drawing
    // Need to be unlocked after start main cycle
    runMutex.lock();

    // Resetting values
    selectedBox = 0;

    // Resetting input
    SDL_Event event;
    while( SDL_PollEvent(&event) != 0 );

    // Starting playing need music (if need)
    if(music){
        data.playMusic(music);
    }
};

//
CycleTemplate::~CycleTemplate(){

};

//
void CycleTemplate::getInput(){
    SDL_Event event;
    while(running){
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
        inputTimer.sleep();
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
    // Running draw cycle
    while (running)
    {
        // Checking for avalible to run
        runMutex.lock();

        // Drawing need scene
        draw();

        // Allowing to continue work
        runMutex.unlock();

        // Waiting for next cycle
        drawTimer.sleep();
    }
};

// Template for draw
void CycleTemplate::draw() const{
    
}

//
void CycleTemplate::run(){
    // Allowing to start work
    runMutex.unlock();
    
    // Waiting for input stop
    getInput();

    // Stopping all side threads
    running = false;
    drawThread.join();
};

