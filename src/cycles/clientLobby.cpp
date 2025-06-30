/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "clientLobby.hpp"


// Base link connections realisations
char baseIP[20] = "::1";
char basePort[20] = "2000";


ClientLobby::ClientLobby(App& _app)
: BaseCycle(_app),
enterIPText{_app.window, {"Enter IP:", "Введите IP:", "-", "Увядзіце IP:"}, 0.5, 0.1, 30, WHITE},
enterPortText{_app.window, {"Enter port:", "Введите порт:", "Port eingeben:", "Увядзіце порт:"}, 0.5, 0.4, 30, WHITE},
cancelButton{_app.window, {"Cancel", "Отмена", "Annullierung", "Адмена"}, 0.5, 0.9, 24, WHITE},
connectButton{_app.window, {"Connect", "Присоединится", "Beitritt", "Далучыцца"}, 0.5, 0.7, 24, WHITE},
enterIPField{_app.window, 0.5, 0.2, 20, baseIP},
enterPortField{_app.window, 0.5, 0.5, 20, basePort}
{
    /*SDLNet_Init();

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
    stop();*/
}

ClientLobby::~ClientLobby() {
    //SDLNet_Quit();
}

void ClientLobby::inputMouseDown(App& _app) {
    // Checking on exit
    if (exitButton.in(mouse) || cancelButton.in(mouse)) {
        _app.startNextCycle(CYCLE_MENU);
        stop();
        return;
    }
    // Clicking in settings menu
    settings.click(mouse);

    // Connection part
    enterIPField.press(mouse);
    enterPortField.press(mouse);

    // Trying to connect
    if (connectButton.in(mouse)) {

    }
    return;
}

void ClientLobby::inputMouseUp(App& app) {
    enterIPField.unpress();
    enterPortField.unpress(); 
}

void ClientLobby::inputKeys(App& app, SDL_Keycode key) {
    enterIPField.type(key);
    enterPortField.type(key);
}

void ClientLobby::update(App& _app) {
    // Updating settings
    settings.update(_app);

    // Updating typeboxes
    mouse.updatePos();
    enterIPField.update(mouse.getX());
    enterPortField.update(mouse.getX());
}

void ClientLobby::inputText(App& app, const char* text) {
    // Inputing text
    enterIPField.writeString(text);
    enterPortField.writeString(text);
}

void ClientLobby::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Drawing buttons
    exitButton.blit(_app.window);

    // Draw main part
    enterIPText.blit(_app.window);
    enterPortText.blit(_app.window);
    cancelButton.blit(_app.window);
    connectButton.blit(_app.window);
    enterIPField.blit();
    enterPortField.blit();

    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
