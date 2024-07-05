/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "SettingsMenu.hpp"

SettingsMenu::SettingsMenu() {}

bool SettingsMenu::click(int mouseX, int mouseY) {
    // Check, if click on setting butoon
    if (settingButton.in(mouseX, mouseY)) {
        active ^= true;  // Changing state
        return true;
    }
    // Clicking in menu
    if (active) {
        // Setting old language to save
        language newLanguage = data.language;

        // Checking, if click on sliders or flag
        if (musicSlider.in(mouseX, mouseY)) {
            holdingSlider = 1;
        } else if (soundSlider.in(mouseX, mouseY)) {
            holdingSlider = 2;
        } else {
            for (language i = LNG_ENGLISH; i < LNG_BELARUSIAN; ++i) {
                if (flags[i].in(mouseX, mouseY)) {
                    newLanguage = i;
                }
            }
        }
        // Updating texts language
        if (newLanguage != data.language) {
            data.language = newLanguage;

            // Updating texture
            data.updateTranslation();
        }
        return false;
    }
    return true;
}

// Getting special input (with mousewheel and escape button)
void SettingsMenu::getAnotherInput(const SDL_Event& event) {
    if (active) {
        // Position of mouse
        int mouseX, mouseY;

        switch (event.type) {
        // Resetting selected box
        case SDL_MOUSEBUTTONUP:
            holdingSlider = 0;
            return;

        case SDL_MOUSEWHEEL:
            // Getting new mouse position on screen
            SDL_GetMouseState(&mouseX, &mouseY);

            // Checking scroll on sliders
            if (musicSlider.scroll(event.wheel.y, mouseX, mouseY)) {
                Mix_VolumeMusic(data.musicVolume);
            } else if (soundSlider.scroll(event.wheel.y, mouseX, mouseY)) {
                Mix_Volume(-1, data.soundsVolume);
            }
            return;

        default:
            return;
        }
    }
}

void SettingsMenu::update() {
    if (active) {
        // Horizontal position of mouse
        int mouseX = 0;

        // Updating pressing on sliders
        switch (holdingSlider) {
        case 1:
            // Updating music slider state
            SDL_GetMouseState(&mouseX, nullptr);
            musicSlider.setValue(mouseX);
            Mix_VolumeMusic(data.musicVolume);
            break;

        case 2:
            // Updating sound slider state
            SDL_GetMouseState(&mouseX, nullptr);
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
}

void SettingsMenu::blit() const {
    // Draw pause button
    settingButton.blit();

    // Drawing menu if need
    if (active) {
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
    }
}

void SettingsMenu::activate() {
    active ^= true;  // Changing state
}
