/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "pauseCycle.hpp"

// Game variants
#include "game/twoPlayer.hpp"
#include "game/server.hpp"
#include "game/client.hpp"

// Starting basic template with main theme
SelectCycle::SelectCycle() : CycleTemplate(MUS_MENU_THEME) {}

// Getting selected button
Uint8 SelectCycle::mouseInput() {
    if (settingButton.in(mouseX, mouseY)) {
        // Staring pause cycle
        return runCycle<PauseCycle>();
    } else if (data.textButtons[BTN_SELECT_SINGLE].in(mouseX, mouseY)) {
        // Staring two-player mode cycle
        return runCycle<TwoPlayerGameCycle>();
    } else if (data.textButtons[BTN_SELECT_TWO].in(mouseX, mouseY)) {
        // Staring two-player mode cycle
        return runCycle<TwoPlayerGameCycle>();
    } else if (data.textButtons[BTN_SELECT_SERVER].in(mouseX, mouseY)) {
        // Staring server mode cycle
        return runCycle<ServerGameCycle>();
    } else if (data.textButtons[BTN_SELECT_CLIENT].in(mouseX, mouseY)) {
        // Staring client mode cycle
        return runCycle<ClientGameCycle>();
    }

    // None-return
    return 0;
}

// Drawing background with all buttons
void SelectCycle::draw() const {
    // Bliting background
    data.setColor(BLACK);
    SDL_RenderClear(data.renderer);

    // Bliting title
    data.texts[TXT_SELECT_TITLE].blit();

    // Blitting buttons
    // Start variants
    for (Uint8 i=BTN_SELECT_SINGLE; i <= BTN_SELECT_CLIENT; ++i) {
        data.textButtons[i].blit();
    }
    // Settings menu
    settingButton.blit();

    // Bliting all to screen
    data.render();
}
