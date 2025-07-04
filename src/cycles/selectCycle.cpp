/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"


// Starting basic template with main theme
SelectCycle::SelectCycle(const App& _app)
: BaseCycle(_app),
titleText{_app.window, {"Chess", "Шахматы", "Schach", "Шахматы"}, 0.5, 0.1, 3, 64, WHITE},
singleplayerButton{_app.window, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}, 0.5, 0.3, 24, WHITE},
twoPlayerButton{_app.window, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}, 0.5, 0.5, 24, WHITE},
serverButton{_app.window, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}, 0.5, 0.7, 24, WHITE},
connectButton{_app.window, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}, 0.5, 0.9, 24, WHITE} {
    // Resetting figures color
    for (unsigned i=IMG_GAME_WHITE_PAWN; i<=IMG_GAME_BLACK_KING; ++i) {
        _app.window.setColorMode(IMG_names(i));
    }

    // Starting menu song (if wasn't started)
    if(!isRestarted()) {
        _app.music.start(MUS_MENU);
    }
}

// Getting selected button
void SelectCycle::inputMouseDown(App& _app) {
    if (settings.click(mouse)) {
        // Updating location
        _app.window.updateTitle();
        restart();
        return;
    } else if (!settings.isActive()) {
        if (singleplayerButton.in(mouse)) {
            _app.startNextCycle(CYCLE_SINGLEPLAYER);
            stop();
        } else if (twoPlayerButton.in(mouse)) {
            _app.startNextCycle(CYCLE_LOCALCOOP);
            stop();
        } else if (serverButton.in(mouse)) {
            _app.startNextCycle(CYCLE_SERVER_LOBBY);
            stop();
        } else if (connectButton.in(mouse)) {
            _app.startNextCycle(CYCLE_CLIENT_LOBBY);
            stop();
        }
    }
    return;
}

// Example for getting keys input
void SelectCycle::inputKeys(App& _app, SDL_Keycode _key) {
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
