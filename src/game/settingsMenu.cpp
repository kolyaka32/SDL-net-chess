/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "settingsMenu.hpp"

SettingsMenu::SettingsMenu(const App& _app)
: settingButton{_app.window, 0.95, 0.05, IMG_GUI_PAUSE_BUTTON},
background{_app.window, 0.5, 0.5, 0.65, 0.8, 20, 5},
titleText{_app.window, {"Pause", "Пауза", "Pause", "Паўза"}, 34, 0.5, 0.15, 2, WHITE},
flags {
    {_app.window, 0.35, 0.28, IMG_GUI_FLAG_USA},
    {_app.window, 0.65, 0.28, IMG_GUI_FLAG_RUS},
    {_app.window, 0.35, 0.47, IMG_GUI_FLAG_GER},
    {_app.window, 0.65, 0.47, IMG_GUI_FLAG_BEL},
},
musicText{_app.window, {"Music", "Музыка", "Die Musik", "Музыка"}, 30, 0.5, 0.6, 1, WHITE},
musicSlider{_app.window, 0.5, 0.66, _app.music.getVolume()},
soundText{_app.window, {"Sounds", "Звуки", "Geräusche", "Гук"}, 30, 0.5, 0.72, 1, WHITE},
soundSlider{_app.window, 0.5, 0.78, _app.sounds.getVolume()},
exitButton{_app.window, {"Exit", "Выход", "Ausfahrt", "Выхад"}, 24, 0.5, 0.85, WHITE} {}

bool SettingsMenu::click(int mouseX, int mouseY) {
    // Check, if click on setting butoon
    if (settingButton.in(mouseX, mouseY)) {
        active ^= true;  // Changing state
        return false;
    }
    // Clicking in menu
    if (active) {
        // Checking on exit
        if (exitButton.in(mouseX, mouseY)) {
            active = false;
            return false;
        }
        // Setting old language to save
        LNG_types newLanguage = currentLanguage;

        // Checking, if click on sliders or flag
        if (musicSlider.in(mouseX, mouseY)) {
            holdingSlider = 1;
        } else if (soundSlider.in(mouseX, mouseY)) {
            holdingSlider = 2;
        } else {
            for (unsigned i = LNG_ENGLISH; i <= LNG_BELARUSIAN; ++i) {
                if (flags[i].in(mouseX, mouseY)) {
                    newLanguage = LNG_types(i);
                }
            }
        }
        // Updating texts language
        if (newLanguage != currentLanguage) {
            currentLanguage = newLanguage;
            
            // Returning need restart
            return true;
        }
    }
    return false;
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
            if (musicSlider.in(mouseX, mouseY)) {
                _app.music.setVolume(musicSlider.scroll(_event.wheel.y));
            } else if (soundSlider.in(mouseX, mouseY)) {
                _app.sounds.setVolume(soundSlider.scroll(_event.wheel.y));
            }
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
            _app.music.setVolume(musicSlider.setValue(mouseX)/2);
            break;

        case 2:
            // Updating sound slider state
            SDL_GetMouseState(&mouseX, nullptr);
            _app.sounds.setVolume(soundSlider.setValue(mouseX)/2);

            // Playing sound effect for understanding loud
            if (getTime() > nextSound) {
                _app.sounds.play(SND_TURN);

                nextSound = getTime() + 400;
            }
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
        soundSlider.blit(_target);
        soundText.blit(_target);
        musicSlider.blit(_target);
        // Quit
        exitButton.blit(_target);
    }
}

void SettingsMenu::activate() {
    active ^= true;  // Changing state
}

bool SettingsMenu::isActive() {
    return active;
}
