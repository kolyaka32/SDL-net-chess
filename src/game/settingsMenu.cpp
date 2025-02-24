/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "settingsMenu.hpp"

SettingsMenu::SettingsMenu(const Window& _target)
: settingButton{_target, 0.95, 0.05, IMG_GUI_PAUSE_BUTTON},
background{_target, 0.5, 0.5, 0.65, 0.7, 20, 5},
titleText{_target, {"Pause", "Пауза", "Pause", "Паўза"}, 30, 0.5, 0.2},
flags { {_target, 0.35, 0.33, IMG_GUI_FLAG_USA},
    {_target, 0.65, 0.33, IMG_GUI_FLAG_RUS},
    {_target, 0.35, 0.53, IMG_GUI_FLAG_GER},
    {_target, 0.65, 0.53, IMG_GUI_FLAG_BEL}, },
musicText{_target, {"Music", "Музыка", "Die Musik", "Музыка"}, 30, 0.5, 0.65},
soundText{_target, {"Sounds", "Звуки", "Geräusche", "Гук"}, 30, 0.5, 0.75} {}

bool SettingsMenu::click(int mouseX, int mouseY) {
    // Check, if click on setting butoon
    if (settingButton.in(mouseX, mouseY)) {
        active ^= true;  // Changing state
        return true;
    }
    // Clicking in menu
    if (active) {
        // Setting old language to save
        LNG_types newLanguage = currentLanguage;

        // Checking, if click on sliders or flag
        /*if (musicSlider.in(mouseX, mouseY)) {
            holdingSlider = 1;
        } else if (soundSlider.in(mouseX, mouseY)) {
            holdingSlider = 2;
        } else*/ {
            for (unsigned i = LNG_ENGLISH; i < LNG_BELARUSIAN; ++i) {
                if (flags[i].in(mouseX, mouseY)) {
                    newLanguage = LNG_types(i);
                }
            }
        }
        // Updating texts language
        if (newLanguage != currentLanguage) {
            currentLanguage = newLanguage;

            // Updating texture
            //data.updateTranslation();
        }
        return false;
    }
    return true;
}

// Getting special input (with mousewheel and escape button)
void SettingsMenu::getAnotherInput(App& _app, const SDL_Event& _event) {
    if (active) {
        // Position of mouse
        float mouseX, mouseY;

        switch (_event.type) {
        // Resetting selected box
        case SDL_EVENT_MOUSE_BUTTON_UP:
            holdingSlider = 0;
            return;

        case SDL_EVENT_MOUSE_WHEEL:
            // Getting new mouse position on screen
            SDL_GetMouseState(&mouseX, &mouseY);

            // Checking scroll on sliders
            /*if (musicSlider.scroll(_event.wheel.y, mouseX, mouseY)) {
                _app.music.setVolume(12);
            } else if (soundSlider.scroll(_event.wheel.y, mouseX, mouseY)) {
                _app.sounds.setVolume(12);
            }*/
            return;
        }
    }
}

void SettingsMenu::update(App& _app) {
    if (active) {
        // Horizontal position of mouse
        float mouseX;

        // Updating pressing on sliders
        switch (holdingSlider) {
        case 1:
            // Updating music slider state
            SDL_GetMouseState(&mouseX, nullptr);
            //musicSlider.setValue(mouseX);
            //_app.music.setVolume();
            break;

        case 2:
            // Updating sound slider state
            SDL_GetMouseState(&mouseX, nullptr);
            //soundSlider.setValue(mouseX);
            //_app.sounds.setVolume();

            // Playing sound effect for understanding loud
            #if SCROLLER_SOUND
            if (getTime() > nextSound) {
                _app.sounds.play(SND_TURN);

                nextSound = getTime() + 400;
            }
            #endif
            break;
        }
    }
}

void SettingsMenu::blit(const Window& _target) const {
    // Draw pause button
    settingButton.blit(_target);

    // Drawing menu if need
    if (active) {
        background.blit(_target);
        titleText.blit(_target);

        // Blitting language buttons
        for (unsigned i = 0; i < LNG_count; ++i) {
            flags[i].blit(_target);
        }

        // Sliders
        musicText.blit(_target);
        //soundSlider.blit(_target);
        soundText.blit(_target);
        //musicSlider.blit(_target);
    }
}

void SettingsMenu::activate() {
    active ^= true;  // Changing state
}
