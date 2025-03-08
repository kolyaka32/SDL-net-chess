/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "client.hpp"

Client::Client(App& _app)
: BaseCycle(_app),
app(_app) {
    // Starting main song (if wasn't started)
    if(!isRestarted()) {
        //_app.music.start(MUS_MAIN);
    }
    SDLNet_Init();

    SDLNet_Address* sendTo = SDLNet_ResolveHostname("255.255.255.255");
    SDLNet_WaitUntilResolved(sendTo, -1);
    SDL_Log("Client to send created: %u\n", sendTo);

    //SDLNet_Address* sendFrom = SDLNet_ResolveHostname("127.0.0.1");
    //SDLNet_WaitUntilResolved(sendFrom, -1);

    SDLNet_DatagramSocket* current = SDLNet_CreateDatagramSocket(0, 0);

    SDL_Log("Client from send to: %u\n", current);
    SDL_Log(SDL_GetError());

    char data[20] = "1234";
    
    SDLNet_SendDatagram(current, sendTo, 8000, data, 20);

    SDL_Log(SDL_GetError());

    SDLNet_DestroyDatagramSocket(current);
    SDLNet_UnrefAddress(sendTo);
    
    SDL_Log("Client stopped\n");

    _app.startNextCycle(CYCLE_MENU);
    stop();
}

Client::~Client() {
    SDLNet_Quit();
}

void Client::getMouseInput(App& _app) {
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

void Client::update(App& _app) {

    // Updating settings
    settings.update(_app);
}

void Client::draw(const App& _app) const {
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
