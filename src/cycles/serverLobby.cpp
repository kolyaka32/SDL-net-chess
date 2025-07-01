/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"


ServerLobby::ServerLobby(App& _app)
: BaseCycle(_app),
app(_app) {
    // Starting main song (if wasn't started)
    if(!isRestarted()) {
        //_app.music.start(MUS_MAIN);
    }
    NET_Init();

    // Creating server
    server = NET_CreateDatagramSocket(nullptr, 8000);

    SDL_Log("Server created: %u\n", server);
}

ServerLobby::~ServerLobby() {
    NET_DestroyDatagramSocket(server);
    NET_Quit();
}

void ServerLobby::inputMouseDown(App& _app) {
    // Checking on exit
    if (exitButton.in(mouse)) {
        _app.startNextCycle(CYCLE_MENU);
        stop();
        return;
    }
    // Clicking in settings menu
    settings.click(mouse);
    return;
}

void ServerLobby::update(App& _app) {

    // Updating settings
    settings.update(_app);

    NET_Datagram* data;


    if (!NET_ReceiveDatagram(server, &data)) {
        SDL_Log("something");
    }

    if (!NET_ReceiveDatagram(server, &data)) {
        SDL_Log("something");
    }

    if (data) {
        SDL_Log("Error: %s\n", SDL_GetError());
        for (int i=0; i < data->buflen; ++i) {
            SDL_Log("%c ", data->buf[i]);
        }
        NET_DestroyDatagram(data);
    }
}

void ServerLobby::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Drawing buttons
    exitButton.blit(_app.window);

    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
