/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"


// Static class members
bool CycleTemplate::restarted = false;

// Reset basic cycle template variables
CycleTemplate::CycleTemplate()
: mouseX(0), mouseY(0) {
    // Resetting input
    SDL_Event event;
    while ( SDL_PollEvent(&event) != 0 ) {}
}

void CycleTemplate::updateMousePos() {
    SDL_GetMouseState(&mouseX, &mouseY);
}

void CycleTemplate::stop() {
    running = false;
}

void CycleTemplate::restart() {
    restarted = true;
    running = false;
}

bool CycleTemplate::isRestarted() {
    return restarted;
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
            _app.stop();

            // Stopping current cycle
            running = false;
            return;

        // Getting mouse input
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            updateMousePos();
            inputMouseDown(_app);
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            updateMousePos();
            inputMouseUp(_app);
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            updateMousePos();
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
    /*if (startOptions[0].in(mouseX, mouseY)) {
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
    // if (MusicSlider.scroll(event.wheel.y, mouseX, mouseY));
    // else if (SoundSlider.scroll(event.wheel.y, mouseX, mouseY));
}

// Example for getting text input
void CycleTemplate::inputText(App& app, const char* text) {
    // typeBox.writeString(event.text.text);
    // press = false;
}



// Function for start need cycle
void CycleTemplate::run(App& _app) {
    // Resetting restart flag after all started
    restarted = false;

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
