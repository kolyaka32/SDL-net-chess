#include "include.hpp"
#include "define.hpp"
#include "pause.hpp"
//#include "gameSingle.hpp"

// Types of selected box
enum{  
    NORMAL_BOX,
    MUSIC_SLIDER_BOX,
    EFFECT_SLIDER_BOX,
    ENGLISH_BOX,
    RUSSIAN_BOX,
    ESCAPE_BOX
} SELCTED_BOX_types;


// Global HUD
//GUI::Button esc = {0.9, 0.1, IMG_MENU_PAUSE};




// Pause menu
/*void pause(){
    // Save time, when pause start
    timer saveTimer = SDL_GetTicks64();

    // Creating pause text
    GUI::Slider MusicSlider(0.7);
    GUI::Slider SoundSlider(0.9);
    GUI::Button flags[LNG_count] = {
        {0.25, 0.35, IMG_FLAG_USA },
        {0.75, 0.35, IMG_FLAG_RUS }
    };

    MusicSlider.state = MusicVolume;
    SoundSlider.state = EffectsVolume;

    for(Uint8 i=0; i < LNG_count; ++i){
        flags[i].init();
    }

    SDL_Event event;
    bool waiting = true;
    bool MouseDown = false;
    char inBox = NORMAL_BOX;
    LNG_types newLanguage = language;
    Uint8 backMove = 0;

    #if SCROLLER_SOUND
    time prevSND = SDL_GetTicks64();
    #endif

    // Starting loop for waiting for start
    while(waiting){  
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                waiting = false;
                break;

            case SDL_MOUSEWHEEL:
                // Mouse position on screen
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Checking scroll on sliders
                if(MusicSlider.scroll(event.wheel.y, MouseX, MouseY));
                else if(SoundSlider.scroll(event.wheel.y, MouseX, MouseY));
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    waiting = false;  // Returning to game
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                MouseDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                MouseDown = false; 
                inBox = NORMAL_BOX;
            }
        }

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
            else if(flags[0].in(MouseX, MouseY)){
                inBox = ENGLISH_BOX;
            }
            else if(flags[1].in(MouseX, MouseY)){
                inBox = RUSSIAN_BOX;
            }
            else if(esc.in(MouseX, MouseY)){
                inBox = ESCAPE_BOX;
            }
            else{
                inBox = NORMAL_BOX;
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
        case ENGLISH_BOX:  // If touch english language box
            newLanguage = LNG_ENGLISH;
            break;
        case RUSSIAN_BOX:  // If touch russian language box
            newLanguage = LNG_RUSSIAN;
            break;
        case ESCAPE_BOX:
            waiting = false;
            break;
        }

        // Checking for changing language
        if(newLanguage != language){
            language = newLanguage;
            updateTranslation(language);
        }

        // Drawing
        SDL_RenderClear(renderer);
         
        // Showing extra text
        texts[TXT_PAUSE_PAUSE].blit();
        texts[TXT_PAUSE_MUSIC].blit();
        texts[TXT_PAUSE_SOUND].blit();
        // Drawing sliders
        MusicSlider.blit();
        SoundSlider.blit();
        // Drawing buttons
        esc.blit();
        for(Uint8 i=0; i < LNG_count; ++i){
            flags[i].blit();
        }

        // Blitting textures on screen
        SDL_RenderPresent(renderer);

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
};


void selectMenu(){
    GUI::Button buttons[] = {
        {0.5, 0.3, IMG_MENU_BUTTON, texts + TXT_SELECT_SINGLE},
        {0.5, 0.5, IMG_MENU_BUTTON, texts + TXT_SELECT_TWO},
        {0.5, 0.7, IMG_MENU_BUTTON, texts + TXT_SELECT_SERVER},
        {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_SELECT_CLIENT}
    };

    for(Uint8 i=0; i < 4; ++i){
        buttons[i].init();
    }

    // Starting loop for waiting for start
    running = true;
    SDL_Event event;
    while(running){
        while( SDL_PollEvent(&event) != 0 ){  // Getting events
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                break;
            
            case SDL_KEYDOWN:
                // Going to pause menu by escape button
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    pause();
                }
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if(esc.in(MouseX, MouseY)){  // Clicking on escape button
                    pause();
                }
                else if(buttons[0].in(MouseX, MouseY)){
                    singleMainCycle();
                }
                else if(buttons[1].in(MouseX, MouseY)){
                    twoMainCycle();
                }
                else if(buttons[2].in(MouseX, MouseY)){
                    multiMainServer();
                }
                else if(buttons[3].in(MouseX, MouseY)){
                    multiMainClient();
                }
                break;
            }
        }
        // Drawing
        SDL_RenderClear(renderer);

        // Drawing GUI
        texts[TXT_SELECT_ENTER].blit();

        // Drawing buttons with signes on it
        for(Uint8 i=0; i < 4; ++i){
            buttons[i].blit();
        }

        esc.blit();
        #if ADEVERTISMENT
        if(advertisingMode){
            MenuAdvertisment.blit();
        }
        #endif
        SDL_RenderPresent(renderer);

        SDL_Delay( 1000/drawFPS );    // Delaying constant time between ticks to decrease CPU loading
    }
    // Clearing animations
    #if ADEVERTISMENT
    if(advertisingMode){
        MenuAdvertisment.clear();
    }
    #endif

    // Starting playing main game theme
    //Mix_PlayMusic( Musics[MUS_MAIN_THEME], -1 );
}*/