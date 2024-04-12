#include "define.hpp"
#include "pauseCycle.hpp"
#include "GUI/slider.cpp"


// Types of selected box
enum{  
    BOX_NORMAL,
    BOX_MUSIC_SLIDER,
    BOX_SOUND_SLIDER,
    BOX_ENGLISH,
    BOX_RUSSIAN,
    BOX_GERMAN,
    BOX_BELLARUSIAN,
    BOX_ESCAPE
} SELECTED_BOX_types;


//
PauseCycle::PauseCycle() : CycleTemplate(MUS_START_NONE){

};

//
PauseCycle::~PauseCycle(){

};

//
void PauseCycle::getInput(){
    SDL_Event event;
    while(true){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                data.running = false;
                return;

            case SDL_MOUSEWHEEL:
                // Mouse position on screen
                SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position

                // Checking scroll on sliders
                if(musicSlider.scroll(event.wheel.y, mouseX, mouseY));
                else if(soundSlider.scroll(event.wheel.y, mouseX, mouseY));
                break;

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
        // Updating selected box
        switch (selectedBox)
        {
        case BOX_MUSIC_SLIDER:
            // Updating music slider state
            SDL_GetMouseState(&mouseX, &mouseY);
            musicSlider.setValue(mouseX);
            Mix_VolumeMusic(data.musicVolume);
            break;

        case BOX_SOUND_SLIDER:
            // Updating sound slider state
            SDL_GetMouseState(&mouseX, &mouseY);
            soundSlider.setValue(mouseX);
            Mix_Volume(-1, data.soundsVolume);

            // Playing sound effect for understanding loud
            #if SCROLLER_SOUND
            if( SDL_GetTicks64() > nextSound ){
                data.playSound(SND_TURN);
                nextSound = SDL_GetTicks64() + 400;
            }
            #endif
            break;
        }
        
        // Waiting next cycle
        data.waitDraw();
    }
};

//
Uint8 PauseCycle::mouseInput(){
    //
    Uint8 newLanguage = data.language;

    //
    if(settingButton.in(mouseX, mouseY)){
        return 1;
    }
    else if(musicSlider.in(mouseX, mouseY)){
        selectedBox = BOX_MUSIC_SLIDER;
        return 0;
    }
    else if(soundSlider.in(mouseX, mouseY)){
        selectedBox = BOX_SOUND_SLIDER;
        return 0;
    }
    else for(Uint8 i=0; i < LNG_count; ++i){
        if(flags[i].in(mouseX, mouseY)){
            newLanguage = i;
        }
    }
    
    // Updating texts language
    if(newLanguage != data.language){
        data.language = newLanguage;
        // Locking drawing for updating
        runMutex.lock();

        // Updating texture
        data.updateTranslation();

        // Allowing to continue draw
        runMutex.unlock();
    }

    // None-return
    return 0;
};

//
Uint16 offset = 0;

//
void PauseCycle::draw() const{
    // Bliting background
    data.setColor({255, 206, 158, 255});
    SDL_RenderClear(data.renderer);

    // Drawing background
    data.setColor({206, 139, 71, 255});
    for(coord y=0; y <= FIELD_WIDTH; ++y)
        for(coord x=y%2; x <= FIELD_WIDTH; x+=2){
            SDL_Rect rect = {(x-1) * CELL_SIDE + offset/2, (y-1) * CELL_SIDE + offset/2, CELL_SIDE, CELL_SIDE};
            SDL_RenderFillRect(data.renderer, &rect);
        }

    // Moving background
    offset = (offset + 1) % (CELL_SIDE * 2);

    // Bliting title
    data.texts[TXT_PAUSE_TITLE].blit();

    // Blitting buttons
    // Start variants
    for(Uint8 i=0; i < LNG_count; ++i){
        flags[i].blit();
    };

    // Sliders
    data.texts[TXT_PAUSE_MUSIC].blit();
    soundSlider.blit();
    data.texts[TXT_PAUSE_SOUND].blit();
    musicSlider.blit();

    // Settings menu
    settingButton.blit();

    // Bliting all to screen
    data.render();
};
