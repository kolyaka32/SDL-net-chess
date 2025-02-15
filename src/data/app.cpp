/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "../GUI/baseGUI.hpp"

App::App()
 : window{loader},
 music{loader},
 sounds{loader}
{
    // Running current application
    run();
}

App::~App() {

}

void App::run() {
    // Testing
    GUI::TypeBox typeBox{window, 12, 0.5, 0.5};
    GUI::DynamicText dynText{window, {"12 %i", "34 %i", "56 %i", "78 %i"}, 24, 0.5, 0.2};

    // Main part
    bool running = true;
    float mouseX, mouseY;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            // Code of program exiting
            case SDL_EVENT_QUIT:
                // Stopping program at all
                //data.appRunning = false;
    
                // Stopping current cycle
                running = false;
                return;
    
            // Getting mouse input
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                // Updating mouse position
                SDL_GetMouseState(&mouseX, &mouseY);
    
                // Getting mouse press
                /*if (getMouseInput()) {
                    // Stopping run cycle
                    running = false;
                    return;
                }*/
                break;
    
            // Getting mouse presses
            case SDL_EVENT_KEY_DOWN:
                /*if (getKeysInput(event.key.key)) {
                    // Closing cycle, if need
                    running = false;
                    return;
                }*/
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                SDL_GetMouseState(&mouseX, &mouseY);
                //slider.scroll(event.wheel.y, mouseX, mouseY);
                break;
    
            /*default:
                // Getting another user input (if need)
                getAnotherInput(event);*/
            }
        }
        dynText.updateLocationArgs(window, 20);

        // Drawing
        window.setDrawColor(GREEN);
        window.clear();
        dynText.blit(window);
        typeBox.blit(window);
        window.render();
    }
}
