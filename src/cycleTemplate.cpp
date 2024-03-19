#include "cycleTemplate.hpp"




//
CycleTemplate::CycleTemplate(){
    // Resetting values
    //LMBclick = false;
    selectedBox = 0;
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
                mouseInput();
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
void CycleTemplate::mouseInput(){
    /*if(startOptions[0].in(mouseX, mouseY)){

    }*/
};

//
void CycleTemplate::drawing(){
    while (true)
    {
        // Bliting background
        SDL_RenderClear(data.renderer);

        // Bliting text
        //data.texts[TXT_].blit();

        // Bliting all to screen
        data.render();

        // Waiting next cycle
        data.waitDraw();
    }
};

//
void CycleTemplate::run(){
    // Waiting for input stop
    getInput();

    // Stopping all side threads
    drawThread.detach();
};
