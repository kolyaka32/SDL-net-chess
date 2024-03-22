#include "define.hpp"
#include "pauseCycle.hpp"


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




// Pause menu
/*void pause(){


    bool MouseDown = false;

    LNG_types newLanguage = language;
    Uint8 backMove = 0;

    #if SCROLLER_SOUND
    time prevSND = SDL_GetTicks64();
    #endif


        int MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
        if(MouseDown && inBox == NORMAL_BOX){
            // Checking on clicking on any of boxes
            if(MusicSlider.checkIn(MouseX, MouseY)){
                inBox = MUSIC_SLIDER_BOX;
            }
            else if(SoundSlider.checkIn(MouseX, MouseY)){
                inBox = EFFECT_SLIDER_BOX;
            }
        }

        switch(inBox)
        {
        case MUSIC_SLIDER_BOX:  // If touch music slider
            MusicSlider.setValue(MouseX);
            Mix_VolumeMusic(MusicSlider.state);  // Setting volume of music
            break;
        case EFFECT_SLIDER_BOX:  // If touch effects slider
            SoundSlider.setValue(MouseX);
            Mix_Volume(-1, SoundSlider.state);  // Setting volume of effects
            
            // Playing sound effect for understanding loud
            #if SCROLLER_SOUND
            if( SDL_GetTicks64() - prevSND > 200 ){
                Mix_PlayChannel(-1, Sounds[SND_FLAG_SET], 0);
                prevSND = SDL_GetTicks64();
            }
            #endif
            break;

        }
    }
};*/



//
PauseCycle::PauseCycle(){

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
                //runMutex.lock();
                return;

            /*case SDL_MOUSEWHEEL:
                // Mouse position on screen
                SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position

                // Checking scroll on sliders
                //if(MusicSlider.scroll(event.wheel.y, mouseX, mouseY));
                //else if(SoundSlider.scroll(event.wheel.y, mouseX, mouseY));
                break;*/

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    //runMutex.lock();
                    return;
                };
                break;

            case SDL_MOUSEBUTTONDOWN:
                // Getting mouse position
                SDL_GetMouseState(&mouseX, &mouseY);  

                // Getting mouse press 
                if(mouseInput()){
                    //runMutex.lock();
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
            musicSlider.setValue(mouseX);
            break;

        case BOX_SOUND_SLIDER:
            soundSlider.setValue(mouseX);
            break;
        }
        
        // Waiting next cycle
        data.waitInput();
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
    else if(musicSlider.in(mouseX, mouseY)){
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
        data.updateTranslation();
    }

    // None-return
    return 0;
};

//
void PauseCycle::draw(){
    // Bliting background
    SDL_RenderClear(data.renderer);

    // Bliting title
    data.texts[TXT_PAUSE_TITLE].blit();

    // Blitting buttons
    // Start variants
    for(Uint8 i=0; i < LNG_count; ++i){
        flags[i].blit();
    };
    // Settings menu
    settingButton.blit();

    // Bliting all to screen
    data.render();
};
