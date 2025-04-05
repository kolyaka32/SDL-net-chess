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


bool SettingsMenu::click(const Mouse _mouse) {
    // Check, if click on setting butoon
    if (settingButton.in(_mouse)) {
        active ^= true;  // Changing state
        return false;
    }
    // Clicking in menu
    if (active) {
        // Checking on exit
        if (exitButton.in(_mouse)) {
            active = false;
            return false;
        }
        // Setting old language to save
        LNG_types newLanguage = currentLanguage;

        // Checking, if click on sliders or flag
        if (musicSlider.in(_mouse)) {
            holdingSlider = 1;
        } else if (soundSlider.in(_mouse)) {
            holdingSlider = 2;
        } else {
            for (unsigned i = LNG_ENGLISH; i <= LNG_BELARUSIAN; ++i) {
                if (flags[i].in(_mouse)) {
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


void SettingsMenu::unClick() {
    if (active) {
        // Resetting selected box
        holdingSlider = 0;
    }
}

void SettingsMenu::scroll(App& _app, const Mouse mouse, float _wheelY) {
    if (active) {
        // Checking scroll on sliders
        if (musicSlider.in(mouse)) {
            _app.music.setVolume(musicSlider.scroll(_wheelY));
        } else if (soundSlider.in(mouse)) {
            _app.sounds.setVolume(soundSlider.scroll(_wheelY));
        }
    }
}

void SettingsMenu::update(App& _app) {
    if (active) {
        // Creating and finding mouse position
        Mouse mouse;
        mouse.updatePos();

        // Updating pressing on sliders
        switch (holdingSlider) {
        case 1:
            // Updating music slider state
            _app.music.setVolume(musicSlider.setValue(mouse.getX()));
            break;

        case 2:
            // Updating sound slider state
            _app.sounds.setVolume(soundSlider.setValue(mouse.getX()));

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
    // Changing state to opposite
    active ^= true;
}

bool SettingsMenu::isActive() {
    return active;
}
