/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"

// Starting basic template with main theme
SelectCycle::SelectCycle(const Window& _target)
: titleText{_target, {"Chess", "Шахматы", "Schach", "Шахматы"}, 30, 0.5, 0.1, WHITE},
singleplayerButton{_target, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}, 24, 0.5, 0.3, WHITE},
twoPlayerButton{_target, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}, 24, 0.5, 0.5, WHITE},
serverButton{_target, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}, 24, 0.5, 0.7, WHITE},
connectButton{_target, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}, 24, 0.5, 0.9, WHITE} {}

// Getting selected button
void SelectCycle::getMouseInput(App& _app) {
    if (settings.click(mouseX, mouseY)) {
        if (singleplayerButton.in(mouseX, mouseY)) {
            _app.startNextCycle(CYCLE_SINGLEPLAYER);
        } else if (twoPlayerButton.in(mouseX, mouseY)) {
            _app.startNextCycle(CYCLE_LOCALCOOP);
        } else if (serverButton.in(mouseX, mouseY)) {
            _app.startNextCycle(CYCLE_SERVER);
        } else if (connectButton.in(mouseX, mouseY)) {
            _app.startNextCycle(CYCLE_CLIENT);
        }
    }
    return;
}

// Example for getting keys input
void SelectCycle::getKeysInput(App& _app, SDL_Keycode _key) {
    switch (_key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;
    }
}

void SelectCycle::update(App& _app) {
    background.update();
    settings.update(_app);
}

// Drawing background with all buttons
void SelectCycle::draw(const App& _app) const {
    // Bliting background
    background.blit(_app.window);

    // Bliting title
    titleText.blit(_app.window);

    // Blitting start buttons
    singleplayerButton.blit(_app.window);
    twoPlayerButton.blit(_app.window);
    serverButton.blit(_app.window);
    connectButton.blit(_app.window);

    // Settings menu
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
