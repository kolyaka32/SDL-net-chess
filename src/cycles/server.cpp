/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "server.hpp"


Server::Server(App& _app)
: BaseCycle(_app),
app(_app) {
    // Starting main song (if wasn't started)
    if(!isRestarted()) {
        //_app.music.start(MUS_MAIN);
    }
    SDLNet_Init();

    // Creating server
    server = SDLNet_CreateDatagramSocket(NULL, 8000);

    SDL_Log("Server created: %u\n", server);
}

Server::~Server() {
    SDLNet_Quit();
    SDLNet_DestroyDatagramSocket(server);
}

void Server::getMouseInput(App& _app) {
    // Checking on exit
    if (exitButton.in(mouseX, mouseY)) {
        _app.startNextCycle(CYCLE_MENU);
        stop();
        return;
    }
    // Clicking in settings menu
    settings.click(mouseX, mouseY);
    return;
}

void Server::update(App& _app) {

    // Updating settings
    settings.update(_app);


    SDLNet_Datagram* data;


    if (!SDLNet_ReceiveDatagram(server, &data)) {
        SDL_Log("something");
    }

    if (data) {
        SDL_Log("Error %s\n", SDL_GetError());
        for (int i=0; i < data->buflen; ++i) {
            SDL_Log("%u ", data->buf[i]);
        }
        SDL_Log("\n");
        SDLNet_DestroyDatagram(data);
    }
}

void Server::draw(const App& _app) const {
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
