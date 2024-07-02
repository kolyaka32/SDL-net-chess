/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../define.hpp"
#include "pauseCycle.hpp"


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


// Starting without any new song
PauseCycle::PauseCycle() {}

// Getting special input (with mousewheel and escape button)
bool PauseCycle::getAnotherInput(const SDL_Event& event) {
    switch (event.type) {
    // Resetting selected box
    case SDL_MOUSEBUTTONUP:
        selectedBox = 0;
        return false;

    case SDL_MOUSEWHEEL:
        // Getting new mouse position on screen
        SDL_GetMouseState(&mouseX, &mouseY);

        // Checking scroll on sliders
        if (musicSlider.scroll(event.wheel.y, mouseX, mouseY)) {
            Mix_VolumeMusic(data.musicVolume);
        } else if (soundSlider.scroll(event.wheel.y, mouseX, mouseY)) {
            Mix_Volume(-1, data.soundsVolume);
        }
        return false;

    default:
        return false;
    }
}


void PauseCycle::update() {
    // Updating background state
    background.update();

    // Updating pressing on sliders
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
    language newLanguage = data.language;

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
        for (language i=LNG_ENGLISH; i < LNG_BELARUSIAN; ++i) {
            if (flags[i].in(mouseX, mouseY)) {
                newLanguage = i;
            }
        }
    }

    // Updating texts language
    if (newLanguage != data.language) {
        // Update language state
        data.language = newLanguage;

        // Updating texture
        data.updateTranslation();
    }
    return false;
}

// Drawing cells background, language buttons and sound options
void PauseCycle::draw() const {
    background.blit();
    titleText.blit();

    // Blitting language buttons
    for (language i = 0; i < LNG_count; ++i) {
        flags[i].blit();
    }

    // Sliders
    musicText.blit();
    soundSlider.blit();
    soundText.blit();
    musicSlider.blit();

    // Exit button
    settingButton.blit();

    // Bliting all to screen
    data.render();
}
