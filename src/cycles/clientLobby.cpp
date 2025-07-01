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
enterIPText(_app.window, 0.5, 0.1, {"Enter IP:", "Введите IP:", "-", "Увядзіце IP:"}, 30, WHITE),
enterPortText(_app.window, 0.5, 0.4, {"Enter port:", "Введите порт:", "Port eingeben:", "Увядзіце порт:"}, 30, WHITE),
cancelButton(_app.window, 0.5, 0.9, {"Cancel", "Отмена", "Annullierung", "Адмена"}, 24, WHITE),
connectButton(_app.window, 0.5, 0.7, {"Connect", "Присоединится", "Beitritt", "Далучыцца"}, 24, WHITE),
enterIPField(_app.window, 0.5, 0.2, 20, baseIP),
enterPortField(_app.window, 0.5, 0.5, 20, basePort) {
    NET_Init();

    NET_Address* sendTo = NET_ResolveHostname("127.0.0.1");
    NET_WaitUntilResolved(sendTo, -1);
    SDL_Log("Client to send created: %u\n", sendTo);

    NET_DatagramSocket* current = NET_CreateDatagramSocket(0, 0);

    SDL_Log("Client from send to: %u\n", current);
    SDL_Log("Error: %s", SDL_GetError());

    char data[20] = "1234";

    SDL_Log("Trying send packet: %s\n", data);
    NET_SendDatagram(current, sendTo, 8000, data, 20);

    SDL_Log("Error: %s", SDL_GetError());

    NET_DestroyDatagramSocket(current);
    NET_UnrefAddress(sendTo);
    
    SDL_Log("Client stopped\n");
    NET_Quit();

    _app.startNextCycle(CYCLE_MENU);
    stop();
}

ClientLobby::~ClientLobby() {

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
