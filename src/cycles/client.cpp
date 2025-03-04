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

    
    SDLNet_Address* current = SDLNet_ResolveHostname("www.libsdl.org");

    SDLNet_WaitUntilResolved(current, 20);

    SDLNet_StreamSocket* client = SDLNet_CreateClient(current, 80);

    SDL_Log(SDL_GetError());

    // buffer data
    char data[100];

    SDLNet_ReadFromStreamSocket(client, data, 100);


    //
    printf(data);

    SDLNet_DestroyStreamSocket(client);

    SDLNet_UnrefAddress(current);


    /*SDLNet_Address* current = SDLNet_ResolveHostname("26.46.13.88");
    SDLNet_Address* newCurrent = SDLNet_RefAddress(current);
    SDLNet_StreamSocket* client = SDLNet_CreateClient(newCurrent, 8000);


    SDL_Log(SDL_GetError());

    SDLNet_WaitUntilConnected(client, -1);

    char data[20] = "1234";

    SDLNet_WriteToStreamSocket(client, data, 20);

    SDLNet_DestroyStreamSocket(client);
    SDLNet_UnrefAddress(current);

    _app.startNextCycle(CYCLE_MENU);
    stop();*/
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
