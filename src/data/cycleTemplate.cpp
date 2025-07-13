/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"


// Static class members
bool CycleTemplate::running;
bool CycleTemplate::restarting;
bool CycleTemplate::additionalRestart;

// Reset basic cycle template variables
CycleTemplate::CycleTemplate() {
    // Resetting input
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {}
    running = true;
}

void CycleTemplate::stop() {
    running = false;
}

void CycleTemplate::restart() {
    restarting = true;
    running = false;
}

bool CycleTemplate::isRestarted() {
    return restarting;
}

bool CycleTemplate::isAdditionalRestarted() {
    return additionalRestart;
}

// Getting user input
void CycleTemplate::getInput(App& _app) {
    // Creating event for get user input
    SDL_Event event;

    // Getting input
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        // Code of program exiting
        case SDL_EVENT_QUIT:
            // Stopping program at all
            App::stop();
            return;

        // Getting mouse input
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mouse.updatePos();
            inputMouseDown(_app);
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouse.updatePos();
            inputMouseUp(_app);
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            mouse.updatePos();
            inputMouseWheel(_app, event.wheel.y);
            break;

        // Getting keys presses
        case SDL_EVENT_KEY_DOWN:
            inputKeys(_app, event.key.key);
            break;

        // Text inputing
        case SDL_EVENT_TEXT_INPUT:
            inputText(_app, event.text.text);
            break;
        }
    }
}

// Empty template for draw
void CycleTemplate::draw(const App& app) const {}

// Getting special update (if need)
void CycleTemplate::update(App& app) {}


// Getting input
// Example for getting mouse input
void CycleTemplate::inputMouseDown(App& app) {
    /*if (startOptions[0].in(mouse)) {
        return;
    }*/
}

void CycleTemplate::inputMouseUp(App& app) {}

// Example for getting keys input
void CycleTemplate::inputKeys(App& app, SDL_Keycode _key) {
    switch (_key) {
    case SDLK_ESCAPE:
        // Stopping ruuning by escape
        running = false;
        return;
    }
}

// Example for getting mouse wheel input
void CycleTemplate::inputMouseWheel(App& app, float _wheelY) {
    // if (MusicSlider.scroll(event.wheel.y, mouse));
    // else if (SoundSlider.scroll(event.wheel.y, mouse));
}

// Example for getting text input
void CycleTemplate::inputText(App& app, const char* text) {
    // typeBox.writeString(event.text.text);
    // press = false;
}

// Function for start need cycle
void CycleTemplate::run(App& _app) {
    // Resetting restart flag after all started
    restarting = false;
    additionalRestart = false;

    // Starting main cycle
    while (running) {
        // Getting user input
        getInput(_app);

        // Updating things
        update(_app);

        // Drawing interface
        draw(_app);

        // Standing in idle state
        idleTimer.sleep();
    }
}
