/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "singlePlayer.hpp"
#include "twoPlayer.hpp"
#include "serverLobby.hpp"
#include "clientLobby.hpp"


// Starting basic template with main theme
SelectCycle::SelectCycle(const App& _app)
: BaseCycle(_app),
titleText(_app.window, 0.5, 0.1, {"Chess", "Шахматы", "Schach", "Шахматы"}, 3, 64, WHITE),
singleplayerButton(_app.window, 0.5, 0.3, {"Singleplayer", "Одиночная игра", "Einzelspiel", "Адзіночная гульня"}, 24, WHITE),
twoPlayerButton(_app.window, 0.5, 0.5, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}, 24, WHITE),
serverButton(_app.window, 0.5, 0.7, {"Create server", "Создать сервер", "Server erstellen", "Стварыць сервер"}, 24, WHITE),
connectButton(_app.window, 0.5, 0.9, {"Connect", "Присоединиться", "Beitreten", "Далучыцца"}, 24, WHITE),
disconnectedMessageBox(_app.window, {"Connection lost", "Соединение потярено", "Verbindung verloren", "Злучэнне страчана"}, 1),
terminatedMessageBox(_app.window, {"Connection terminated", "Соединение разорвано", "Verbindung unterbrochen", "Злучэнне разарвана"}, 2) {
    // Resetting figures color
    for (unsigned i=IMG_GAME_WHITE_PAWN; i <= IMG_GAME_BLACK_KING; ++i) {
        _app.window.setColorMode(IMG_names(i));
    }

    // Starting menu song (if wasn't started)
    if(!App::isRestarted()) {
        _app.music.start(MUS_MENU);
    }
}

// Getting selected button
void SelectCycle::inputMouseDown(App& _app) {
    if (disconnectedMessageBox.click(mouse)) {
        return;
    }
    if (terminatedMessageBox.click(mouse)) {
        return;
    }
    if (settings.click(mouse)) {
        return;
    }
    if (singleplayerButton.in(mouse)) {
        _app.runCycle<SinglePlayerGameCycle>();
    } else if (twoPlayerButton.in(mouse)) {
        _app.runCycle<TwoPlayerGameCycle>();
    } else if (serverButton.in(mouse)) {
        _app.runCycle<ServerLobby>();
    } else if (connectButton.in(mouse)) {
        _app.runCycle<ClientLobby>();
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
    BaseCycle::update(_app);
    background.update();
}

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

    // Message boxes
    disconnectedMessageBox.blit(_app.window);
    terminatedMessageBox.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
