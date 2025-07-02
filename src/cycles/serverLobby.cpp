/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <ctime>
#include "serverLobby.hpp"


ServerLobby::ServerLobby(App& _app)
: BaseCycle(_app),
app(_app),
titleText(_app.window, 0.5, 0.1, {"Wait for connection", "Ожидайте подключений", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 30, WHITE),
addressText(_app.window, 0.5, 0.3, {"Your address: %s", "Ваш адресс: %s", "Ihre Adresse: %s", "Ваш адрас: %s"}, 30, WHITE),
copiedInfoBox(_app.window, 0.5, 0.37, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}, 30, WHITE),
showAddressText(_app.window, 0.5, 0.45, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}, 24),
hideAddressText(_app.window, 0.5, 0.45, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}, 24) {
    // Initialasing net library
    NET_Init();

    // Finding avaliable server port
    Uint16 currentPort = 8000;

    // Finding avalialble port
    srand(time(0));
    while ((server = NET_CreateDatagramSocket(nullptr, currentPort)) == nullptr) {
        // Creating another port
        currentPort = rand() % 10000;
    }

    // Getting current address
    int addressesNumber = 0;
    NET_Address** addresses = NET_GetLocalAddresses(&addressesNumber);

    // Finding usedull address
    for (int i=0; i < addressesNumber; ++i) {
        const char* address = NET_GetAddressString(addresses[i]);
        bool usefull = true;
        // Check, if not IPv6 address
        for (const char* c = address; *c; ++c) {
            if (*c == ':') {
                usefull = false;
                break;
            }
        }
        // Check, if not basic '127.0.0.1'
        if (usefull && strcmp(address, "127.0.0.1")) {
            // Use this address
            sprintf(currentAddress, "%s:%u", address, currentPort);
            break;
        }
    }
    // Setting showing address text as hidden
    addressText.setValues(_app.window, "********");

    #if CHECK_CORRECTION
    SDL_Log("Server created: %u, address: %s, port: %u", server, currentAddress, currentPort);
    #endif
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
    if (settings.click(mouse)) {
        // Updating location
        _app.window.updateTitle();
        restart();
        return;
    }
    // Check, if in settings menu
    if (settings.isActive()) {
        return;
    }
    // Check on copying address
    if (addressText.in(mouse)) {
        // Copying address to buffer
        static char clipboardText[20];
        strcpy(clipboardText, currentAddress);
        SDL_SetClipboardText(clipboardText);
        copiedInfoBox.reset();
        return;
    }
    if (showAddress) {
        // Check on hiding address
        if (hideAddressText.in(mouse)) {
            showAddress = false;
            addressText.setValues(_app.window, "********");
            return;
        }
    } else {
        // Check on showing address
        if (showAddressText.in(mouse)) {
            showAddress = true;
            addressText.setValues(_app.window, currentAddress);
            return;
        }
    }
}

void ServerLobby::update(App& _app) {
    // Updating settings
    settings.update(_app);

    NET_Datagram* data;

    if (!NET_ReceiveDatagram(server, &data)) {
        //SDL_Log("something: %u", data);
    }

    if (data) {
        // Writing getted data for debug
        #if CHECK_CORRECTION
        SDL_Log("Get packet with %u bytes, from %s, port: %u", data->buflen, NET_GetAddressString(data->addr), data->port);
        for (int i=0; i < data->buflen; ++i) {
            SDL_Log("%u", data->buf[i]);
        }
        #endif
        NET_DestroyDatagram(data);
    }

    // Update infobox
    copiedInfoBox.update();
}

void ServerLobby::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Draw main part
    titleText.blit(_app.window);
    addressText.blit(_app.window);
    copiedInfoBox.blit(_app.window);

    if (showAddress) {
        hideAddressText.blit(_app.window);
    } else {
        showAddressText.blit(_app.window);
    }

    // Drawing buttons
    exitButton.blit(_app.window);

    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
