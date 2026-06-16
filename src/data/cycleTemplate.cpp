/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"


// Static class members
bool CycleTemplate::running;
bool CycleTemplate::restarting;

// Reset basic cycle template variables
CycleTemplate::CycleTemplate(Window& _window)
: window(_window) {
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

// Getting user input
void CycleTemplate::getInput() {
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
            inputMouseDown();
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouse.updatePos();
            inputMouseUp();
            break;

        case SDL_EVENT_MOUSE_WHEEL:
            mouse.updatePos();
            inputMouseWheel(event.wheel.y);
            break;

        // Getting keys presses
        case SDL_EVENT_KEY_DOWN:
            inputKeys(event.key.key);
            break;

        // Text inputing
        case SDL_EVENT_TEXT_INPUT:
            inputText(event.text.text);
            break;
        }
    }
}

// Empty template for draw
void CycleTemplate::draw() const {}

void CycleTemplate::update() {}

bool CycleTemplate::inputMouseDown() {
    return false;
}

void CycleTemplate::inputMouseUp() {}

// Example for getting keys input
bool CycleTemplate::inputKeys(SDL_Keycode _key) {
    /*switch (_key) {
    case SDLK_ESCAPE:
        // Stopping ruuning by escape
        stop();
        return true;
    }*/
   return false;
}

// Example for getting mouse wheel input
bool CycleTemplate::inputMouseWheel(float _wheelY) {
    // if (MusicSlider.scroll(event.wheel.y, mouse));
    // else if (SoundSlider.scroll(event.wheel.y, mouse));
    return false;
}

// Example for getting text input
bool CycleTemplate::inputText(const char* text) {
    // typeBox.writeString(event.text.text);
    return false;
}

// Function for start need cycle
void CycleTemplate::run() {
    // Resetting restart flag after all started
    restarting = false;

    // Starting main cycle
    while (running) {
        // Getting user input
        getInput();

        // Updating things
        update();

        // Drawing interface
        draw();

        // Standing in idle state
        idleTimer.sleep();
    }
}
