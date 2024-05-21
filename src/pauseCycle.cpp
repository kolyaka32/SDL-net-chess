/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "define.hpp"
#include "pauseCycle.hpp"
#include "GUI/slider.cpp"


// Types of selected box
enum {
    BOX_NORMAL,
    BOX_MUSIC_SLIDER,
    BOX_SOUND_SLIDER,
    BOX_ENGLISH,
    BOX_RUSSIAN,
    BOX_GERMAN,
    BOX_BELLARUSIAN,
    BOX_ESCAPE
} SELECTED_BOX_types;


// Starting basic template without start any new song
PauseCycle::PauseCycle() : CycleTemplate(MUS_START_NONE) {}

// Getting special input (with mousewheel and escape button)
bool PauseCycle::getAnotherInput(SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEWHEEL:
        // Mouse position on screen
        SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position
        // Checking scroll on sliders
        if (musicSlider.scroll(event.wheel.y, mouseX, mouseY)) {}
        else
            soundSlider.scroll(event.wheel.y, mouseX, mouseY);
        return false;
    
    default:
        // None-return
        return false;
    }
}

// Special update of selected box
void PauseCycle::update(){
    switch (selectedBox) {
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
        if (SDL_GetTicks64() > nextSound) {
            data.playSound(SND_TURN);
            nextSound = SDL_GetTicks64() + 400;
        }
        #endif
        break;
    }
}

// Getting language change and sound mutting
bool PauseCycle::getMouseInput() {
    // Setting old language to save
    Uint8 newLanguage = data.language;

    // Checking, if click on sliders or flag
    if (settingButton.in(mouseX, mouseY)) {
        return true;
    } else if (musicSlider.in(mouseX, mouseY)) {
        selectedBox = BOX_MUSIC_SLIDER;
        return false;
    } else if (soundSlider.in(mouseX, mouseY)) {
        selectedBox = BOX_SOUND_SLIDER;
        return false;
    } else {
        for (Uint8 i=0; i < LNG_count; ++i)
            if (flags[i].in(mouseX, mouseY)) {
                newLanguage = i;
            }
    }

    // Updating texts language
    if (newLanguage != data.language) {
        // Update language state
        data.language = newLanguage;

        // Updating texture
        data.updateTranslation();
    }

    // None-return
    return false;
}

// Getting button escape from pause
bool PauseCycle::getKeysInput(SDL_Keysym& key) {
    switch (key.sym)
    {
    case SDLK_ESCAPE:
        // Stopping ruuning by escape
        running = false;
        return true;

    default:
        // None-return
        return false;
    }
}

// Extra variables
Uint16 offset = 0;  // Offset of background cells for create move effect

// Drawing cells background, language buttons and sound options
void PauseCycle::draw() const {
    // Bliting background
    data.setColor({255, 206, 158, 255});
    SDL_RenderClear(data.renderer);

    // Drawing background
    data.setColor({206, 139, 71, 255});
    for (coord y = 0; y <= SCREEN_HEIGHT / CELL_SIDE + 1; ++y)
        for (coord x = y % 2; x <= SCREEN_WIDTH / CELL_SIDE + 1; x+=2) {
            SDL_Rect rect = {(x-1) * CELL_SIDE + offset/2, (y-1) * CELL_SIDE + offset/2, CELL_SIDE, CELL_SIDE};
            SDL_RenderFillRect(data.renderer, &rect);
        }

    // Moving background
    offset = (offset + 1) % (CELL_SIDE * 2);

    // Bliting title
    data.texts[TXT_PAUSE_TITLE].blit();

    // Blitting buttons
    // Start variants
    for (Uint8 i = 0; i < LNG_count; ++i) {
        flags[i].blit();
    }

    // Sliders
    data.texts[TXT_PAUSE_MUSIC].blit();
    soundSlider.blit();
    data.texts[TXT_PAUSE_SOUND].blit();
    musicSlider.blit();

    // Settings menu
    settingButton.blit();

    // Bliting all to screen
    data.render();
}
