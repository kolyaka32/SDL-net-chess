/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "targetConnect.hpp"
#include "../internet/internet.hpp"


// Static objects for save inputted parameters
char TargetConnect::baseIP[15] = "127.0.0.1";
char TargetConnect::basePort[6] = "8000";

TargetConnect::TargetConnect(Window& _window)
: SubWindow(_window, 0.5, 0.5, 0.8, 0.8),
IPText(_window, 0.5, 0.2, {"Enter IP:", "Введите IP:", "Geben Sie die IP ein:", "Увядзіце IP:"}, Height::SubTitle),
IPField(_window, 0.5, 0.3, baseIP),
portText(_window, 0.5, 0.4, {"Enter port:", "Введите порт:", "Port eingeben:", "Увядзіце порт:"}, Height::SubTitle),
portField(_window, 0.5, 0.5, basePort),
pasteButton(_window, 0.5, 0.61, {"Paste the address", "Вставить адрес", "Kopierte Adresse", "Уставіць адрас"}),
connectButton(_window, 0.5, 0.72, {"Connect", "Присоединится", "Beitritt", "Далучыцца"}),
closeButton(_window, 0.5, 0.83, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {}

bool TargetConnect::click(const Mouse _mouse) {
    if (active) {
        // Check, if end typing
        IPField.checkOff(_mouse);
        portField.checkOff(_mouse);

        // Check, if start typing
        if (IPField.click(_mouse)) {
            return true;
        }
        if (portField.click(_mouse)) {
            return true;
        }
        if (pasteButton.in(_mouse)) {
            pasteFromClipboard();
            return true;
        }
        if (connectButton.in(_mouse)) {
            tryConnect();
            return true;
        }
        if (closeButton.in(_mouse)) {
            close();
            return true;
        }
    }
    return false;
}

void TargetConnect::unclick() {
    IPField.unclick();
    portField.unclick();
}

bool TargetConnect::press(SDL_Keycode _key) {
    if (active) {
        if (GUI::Code code = IPField.type(_key)) {
            if (code == GUI::Activate) {
                tryConnect();
            }
            return true;
        }
        if (GUI::Code code = portField.type(_key)) {
            if (code == GUI::Activate) {
                tryConnect();
            }
            return true;
        }
        if (_key == SDLK_ESCAPE) {
            close();
            return true;
        }
    }
    return false;
}

bool TargetConnect::write(const char* _text) {
    if (active) {
        IPField.writeString(_text);
        portField.writeString(_text);
        return true;
    }
    return false;
}

void TargetConnect::update() {
    if (active) {
        // Updating typeboxes
        Mouse mouse;
        mouse.updatePos();
        IPField.update(mouse.getX());
        portField.update(mouse.getX());
    }
}

void TargetConnect::pasteFromClipboard() {
    // Getting data from clipboard
    char* clipboard = SDL_GetClipboardText();

    // Check text on correction
    if (clipboard == nullptr) {
        logger.additional("Couldn't get clipboard");
        return;
    }
    // Find IP text (first part)
    int i = 0;
    for (; clipboard[i]; ++i) {
        // Finding : as port separator
        if (clipboard[i] == ':') {
            break;
        }
        // Checking coorection of string
        if (clipboard[i] != '.' && (clipboard[i] < '0' || clipboard[i] > '9')) {
            logger.additional("Wrong clipboard: %s", clipboard);
            SDL_free(clipboard);
            return;
        }
    }
    clipboard[i] = '\0';
    i++;
    // Finding end of port text
    for (int k=i; clipboard[k]; ++k) {
        if (clipboard[k] < '0' || clipboard[k] > '9') {
            clipboard[k] = '\0';
            break;
        }
    }
    logger.additional("From clipboard: IP: %s, port: %s", clipboard, clipboard+i);
    IPField.setString(clipboard);
    portField.setString(clipboard+i);
    SDL_free(clipboard);
}

void TargetConnect::tryConnect() {
    // Checking correction of port text
    char portTextCorrected[7];
    memcpy(portTextCorrected, portField.getString(), 7);
    for (char* c = portTextCorrected; *c; ++c) {
        if (*c < '0' || *c > '9') {
            logger.additional("Couldn't connect - wrong port");
            return;
        }
    }
    // Saving inputted address
    memcpy(baseIP, IPField.getString(), sizeof(baseIP));
    memcpy(basePort, portTextCorrected, sizeof(basePort));
    // Trying connect at specified address
    Destination dest{IPField.getString(), (Uint16)SDL_atoi(portTextCorrected)};
    internet.sendFirst(dest, {ConnectionCode::Init, Uint8(BROADCAST_APP_INDEX)});
}

void TargetConnect::blit() const {
    // Draw main part
    if (active) {
        background.blit();
        IPText.blit();
        IPField.blit();
        portText.blit();
        portField.blit();
        pasteButton.blit();
        connectButton.blit();
        closeButton.blit();
    }
}

void TargetConnect::writeBaseIP(const char* _text) {
    snprintf(baseIP, sizeof(baseIP), "%s", _text);
}

const char* TargetConnect::getBaseIP() {
    return baseIP;
}

void TargetConnect::writeBasePort(const char* _text) {
    snprintf(basePort, sizeof(basePort), "%s", _text);
}

const char* TargetConnect::getBasePort() {
    return basePort;
}
