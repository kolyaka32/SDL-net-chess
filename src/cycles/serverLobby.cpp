/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "serverLobby.hpp"


bool ServerLobbyCycle::showAddress = false;

ServerLobbyCycle::ServerLobbyCycle(Window& _window)
: BaseCycle(_window),
broadcastRecieveSocket(),
titleText(_window, 0.5, 0.15,
    {"Wait for connection", "Ожидайте подключения", "Verbindungen erwarten", "Чакайце падлучэнняў"}, 2, Height::SubTitle),
hideAddressText(_window, 0.5, 0.3,
    {"Your address: **************", "Ваш адресс: **************", "Ihre Adresse: **************", "Ваш адрас: **************"}),
showAddressText(_window, 0.5, 0.3, {"Your address: %s:%d", "Ваш адресс: %s:%d", "Ihre Adresse: %s:%d", "Ваш адрас: %s:%d"},
    Height::Main, WHITE, GUI::Aligment::Midle, internet.getHostName(), internet.getPort()),
copiedInfoBox(_window, 0.5, 0.4, {"Address copied", "Адрес скопирован", "Adresse kopiert", "Скапіяваны адрас"}),
showAddressButton(_window, 0.5, 0.5, {"Show address", "Показать адресс", "Adresse anzeigen", "Паказаць адрас"}),
hideAddressButton(_window, 0.5, 0.5, {"Hide address", "Скрыть адресс", "Adresse verbergen", "Схаваць адрас"}) {
    // Resetting flag of showing address
    if (!isRestarted()) {
        showAddress = false;
    }

    // Openning socket for recieving broadcast
    broadcastRecieveSocket.setRecieveBroadcast();

    logger.additional("Start server lobby cycle");
}

bool ServerLobbyCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    // Check on copying address
    if (hideAddressText.in(mouse)) {
        // Copying address to buffer
        static char clipboardText[24];
        SDL_snprintf(clipboardText, sizeof(clipboardText), "%s:%d", internet.getHostName(), internet.getPort());
        SDL_SetClipboardText(clipboardText);
        copiedInfoBox.reset();
        return true;
    }
    if (showAddress) {
        // Check on hiding address
        if (hideAddressButton.in(mouse)) {
            showAddress = false;
            return true;
        }
    } else {
        // Check on showing address
        if (showAddressButton.in(mouse)) {
            showAddress = true;
            return true;
        }
    }
    return false;
}

void ServerLobbyCycle::update() {
    BaseCycle::update();

    // Update infobox
    copiedInfoBox.update();

    // Getting internet messages (for main connection)
    while (const GetPacket* packet = internet.getNewMessages()) {
        switch (ConnectionCode(packet->getData<Uint8>(0))) {
        case ConnectionCode::Init:
            // Check if app type is match
            if (packet->getData<Uint8>(1) == BROADCAST_APP_INDEX) {
                // Connecting to getted address
                internet.connectTo(Destination{packet->getSourceAddress()});

                // Sending initialisation applying message
                internet.sendAllConfirmed({ConnectionCode::Init, Uint8(BROADCAST_APP_INDEX)});

                // Starting game (as server)
                App::setNextCycle(Cycle::ServerGame);
            }
            return;

        default:
            return;
        }
    }

    // Getting internet messges (for broadcast)
    while (const GetPacket* packet = broadcastRecieveSocket.recieve()) {
        switch (ConnectionCode(packet->getData<Uint8>(0))) {
        case ConnectionCode::Search:
            // Reporting about itself
            internet.sendFirst(Destination{packet->getSourceAddress()}, {ConnectionCode::Server, Uint8(BROADCAST_APP_INDEX)});
            return;

        default:
            return;
        }
    }
}

void ServerLobbyCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Draw main part
    titleText.blit();
    copiedInfoBox.blit();

    if (showAddress) {
        showAddressText.blit();
        hideAddressButton.blit();
    } else {
        hideAddressText.blit();
        showAddressButton.blit();
    }

    // Drawing buttons
    exitButton.blit();

    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}
