/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"


// Reset basic cycle template variables
CycleTemplate::CycleTemplate() {
    // Resetting values
    mouseX = 0;
    mouseY = 0;

    // Resetting input
    SDL_Event event;
    while ( SDL_PollEvent(&event) != 0 ) {}
}

// Getting user input
void CycleTemplate::getInput() {
    // Creating event for get user input
    static SDL_Event event;

    // Getting input
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        // Code of program exiting
        case SDL_QUIT:
            // Stopping program at all
            data.appRunning = false;

            // Stopping current cycle
            running = false;
            return;

        // Getting mouse input
        case SDL_MOUSEBUTTONDOWN:
            // Updating mouse position
            SDL_GetMouseState(&mouseX, &mouseY);

            // Getting mouse press
            if (getMouseInput()) {
                // Stopping run cycle
                running = false;
                return;
            }
            break;

        // Getting mouse presses
        case SDL_KEYDOWN:
            if (getKeysInput(event.key.keysym)) {
                // Closing cycle, if need
                running = false;
                return;
            }
            break;

        default:
            // Getting another user input (if need)
            getAnotherInput(event);
        }
    }
}

// Empty template for draw
void CycleTemplate::draw() const {}

// Getting special update (if need)
void CycleTemplate::update() {}

// Example for getting mouse input
bool CycleTemplate::getMouseInput() {
    /*if (startOptions[0].in(mouseX, mouseY)) {
        return 1;
    }*/
    // Nothing-return
    return false;
}

// Example for getting keys input
bool CycleTemplate::getKeysInput(const SDL_Keysym& key) {
    switch (key.sym) {
    case SDLK_ESCAPE:
        // Stopping ruuning by escape
        running = false;
        return true;

    default:
        // None-return
        return false;
    }
}

// Example function for get user input
bool CycleTemplate::getAnotherInput(const SDL_Event& event) {
    switch (event.type) {
    /*case SDL_MOUSEWHEEL:
        // Mouse position on screen
        SDL_GetMouseState(&mouseX, &mouseY);  // Getting mouse position

        // Checking scroll on sliders
        //if (MusicSlider.scroll(event.wheel.y, mouseX, mouseY));
        //else if (SoundSlider.scroll(event.wheel.y, mouseX, mouseY));
        break;*/

    default:
        return false;
    }
}

// Function for start need cycle
void CycleTemplate::run() {
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
