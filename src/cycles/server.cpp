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
    SDLNet_CreateServer(NULL, 8000);
}

Server::~Server() {
    SDLNet_Quit();
    SDLNet_DestroyServer(server);
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


    if (client_stream == NULL) {
        SDLNet_AcceptClient(server, &client_stream);
    } else {
        int buffer[40];
        SDLNet_ReadFromStreamSocket(client_stream, buffer, 40);
        SDL_Log("Error %s", SDL_GetError());
        for (int i=0; i < 40; ++i) {
            SDL_Log("%u ", buffer[i]);
        }
        SDL_Log("\n");
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
