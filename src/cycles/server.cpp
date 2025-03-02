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
    int adressesNumber = 0;
    SDLNet_Address** addreses = SDLNet_GetLocalAddresses(&adressesNumber);

    for (int i=0; i < adressesNumber; ++i) {
        SDL_Log("Address at %i: %s", i, SDLNet_GetAddressString(addreses[i]));
    }

    SDLNet_FreeLocalAddresses(addreses);

    //SDLNet_Address* currentAddress = SDLNet_ResolveHostname("26.46.13.88");
    server = SDLNet_CreateDatagramSocket(NULL, 8000);

    SDL_Log("Error %s", SDL_GetError());

    //SDL_Log("Server created %s", SDLNet_GetAddressString(server));
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

    SDLNet_Datagram* datagramm;
    
    SDLNet_ReceiveDatagram(server, &datagramm);

    if (datagramm) {
        SDL_Log("Error %s", SDL_GetError());
        for (int i=0; i< datagramm->buflen; ++i) {
            SDL_Log("%u ", datagramm->buf[i]);
        }
        SDL_Log("\n");
        SDLNet_DestroyDatagram(datagramm);
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
