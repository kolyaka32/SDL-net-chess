/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"


ServerLobby::ServerLobby(App& _app)
: BaseCycle(_app),
app(_app),
titleText(_app.window, 0.5, 0.1, {"Wait for connection", "Ожидайте подключений", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 30, WHITE),
addressText(_app.window, 0.5, 0.3, {"Your address: %s", "Ваш адресс: %s", "Ihre Adresse: %s", "Ваш адрас: %s"}, 30, WHITE),
copiedInfoBox(_app.window, 0.5, 0.37, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}, 30, WHITE),
showAddressText(_app.window, 0.5, 0.45, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}, 24),
hideAddressText(_app.window, 0.5, 0.45, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}, 24) {
    // Initialasing internet class
    server.start();

    // Getting string with full address of current app
    sprintf(currentAddress, "%s:%u", server.getLocalIP(), server.getPort());

    // Setting showing address text as hidden
    addressText.setValues(_app.window, "********");
}

void ServerLobby::inputMouseDown(App& _app) {
    // Checking on exit
    if (exitButton.in(mouse)) {
        server.stop();
        _app.startNextCycle(CYCLE_MENU);
        stop();
        return;
    }
    // Clicking in settings menu
    if (settings.click(mouse)) {
        // Updating location
        server.stop();
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

    // Update infobox
    copiedInfoBox.update();

    // Getting internet packets
    switch (server.getCode()) {
    case ConnectionCode::Init:
        // Sending approving code
        server.connectToLastMessage();

        // Starting game (as server)
        _app.startNextCycle(CYCLE_SERVER_GAME);
        stop();
        break;
    }
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
