/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "../GUI/baseGUI.hpp"

App::App()
: window{loader},
music{loader},
sounds{loader} {
    // Running current application
    run();
}

App::~App() {}

void App::run() {
    // Testing
    GUI::TypeBox typeBox{window, 20, 0.5, 0.5, "123456789"};
    GUI::TextButton btn{window, {"12", "34", "56", "78"}, 40, 0.4, 0.2};
    bool press = false;
    bool selected = false;

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
                if (typeBox.in(mouseX, mouseY)) {
                    if (!selected) {
                        press = true;
                        selected = true;
                        typeBox.select(mouseX);
                    } else {
                        typeBox.removeSelect();
                        typeBox.select(mouseX);
                        press = true;
                    }
                } else if (selected) {
                    selected = false;
                    press = false;
                    typeBox.removeSelect();
                }

                // Getting mouse press
                /*if (getMouseInput()) {
                    // Stopping run cycle
                    running = false;
                    return;
                }*/
                break;
            
            case SDL_EVENT_MOUSE_BUTTON_UP:
                /*if (press) {
                    typeBox.removeSelect();
                    press = false;
                }*/
                press = false;
                break;
    
            // Getting mouse presses
            case SDL_EVENT_KEY_DOWN:
                typeBox.press(event.key.key);
                press = false;
                /*if (getKeysInput(event.key.key)) {
                    // Closing cycle, if need
                    running = false;
                    return;
                }*/
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                //SDL_GetMouseState(&mouseX, &mouseY);
                break;

            case SDL_EVENT_TEXT_INPUT:
                typeBox.writeString(event.text.text);
                press = false;
                break;
    
            /*default:
                // Getting another user input (if need)
                getAnotherInput(event);*/
            }
        }
        if (press) {
            SDL_GetMouseState(&mouseX, &mouseY);
            typeBox.updateSelection(mouseX);
        }
        if (selected) {
            typeBox.updateCaret();
        }
        // Drawing
        window.setDrawColor(GREEN);
        window.clear();
        typeBox.blit();
        btn.blit(window);
        window.render();
    }
}
