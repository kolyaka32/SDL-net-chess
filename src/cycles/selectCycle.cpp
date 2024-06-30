/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "pauseCycle.hpp"

// Game variants
#include "singlePlayer.hpp"
#include "twoPlayer.hpp"
#include "server.hpp"
#include "client.hpp"

// Starting basic template with main theme
SelectCycle::SelectCycle() : BaseCycle(MUS_MENU_THEME) {}

// Getting selected button
bool SelectCycle::getMouseInput() {
    if (settingButton.in(mouseX, mouseY)) {
        return runCycle<PauseCycle>();
    } else if (singleplayerButton.in(mouseX, mouseY)) {
        return runCycle<SinglePlayerGameCycle>();
    } else if (twoPlayerButton.in(mouseX, mouseY)) {
        return runCycle<TwoPlayerGameCycle>();
    } else if (serverButton.in(mouseX, mouseY)) {
        return runCycle<ServerGameCycle>();
    } else if (connectButton.in(mouseX, mouseY)) {
        return runCycle<ClientGameCycle>();
    }

    // Nothing allowable pressed
    return false;
}

// Example for getting keys input
bool SelectCycle::getKeysInput(const SDL_Keysym& key) {
    switch (key.sym) {
    case SDLK_ESCAPE:
        // Running pause menu
        return runCycle<PauseCycle>();

    default:
        // None-return
        return false;
    }
}

// Drawing background with all buttons
void SelectCycle::draw() const {
    // Bliting background
    data.setColor(BLACK);
    SDL_RenderClear(data.renderer);

    // Bliting title
    titleText.blit();

    // Blitting start buttons
    singleplayerButton.blit();
    twoPlayerButton.blit();
    serverButton.blit();
    connectButton.blit();

    // Settings menu
    settingButton.blit();

    // Bliting all to screen
    data.render();
}
