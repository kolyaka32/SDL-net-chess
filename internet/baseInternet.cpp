/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseInternet.hpp"
#include "../data.hpp"


// Base internet interface
// Creating send and recieve data structures
Internet::Internet() {
    // Allocating memory to send and recieve packets
    recieveData = SDLNet_AllocPacket(INTERNET_BUFFER);

    // Setting timer to max value for don't check correction before start
    lastMessageArrive = (timer)-1;
}

// Sending close message and deleting all data
Internet::~Internet() {
    // Sending message of server disabling connection
    sendNew(MES_STOP);

    // Closing port
    SDLNet_UDP_Close(socket);

    // Freeing all packets
    SDLNet_FreePacket(recieveData);
}

//
void Internet::showDisconect() {
    switch (data.language) {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
            "Disconect", "Your connection lost, server disconect", data.window);
        break;

    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
            "Соединение потеряно", "Соединение потерено, сервер отключён", data.window);
        break;
    }
}

// Function of showing connection normal stop
void Internet::showStopConnection() {
    switch (data.language) {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
            "Connection stopped", "Connection stopped by another side", data.window);
        break;

    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
            "Соединение остановлено", "Соединение остановлено по инициативе второй стороны", data.window);
        break;
    }
}

//
void Internet::showCantConnect() {
    switch (data.language) {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
            "Can't connect", "Can't connect to given address", data.window);
        break;

    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
            "Невозможно присоединится", "Невозможно присоединится по указанному адресу", data.window);
        break;
    }
}

// Check, if too much time since last message send
void Internet::checkSendTimeout() {
    // Checking, if need to send NULL-message
    if (SDL_GetTicks64() > lastMessageSend) {
        sendWithoutApply(MES_NONE);
    }
}

// Check, if get new message
bool Internet::checkGetMessage() {
    // Checking if get new data
    while (SDLNet_UDP_Recv(socket, recieveData)) {
        // Resetting arriving timer
        lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;

        // Checking on default messages
        switch (recieveData->data[0]) {
        // Code of nothing
        case MES_NONE:
            return false;

        // Code of closing game - going to menu
        case MES_STOP:
            showStopConnection();
            return true;

        // Code of applaying last message
        case MES_APPL:
            applyMessage(recieveData->data[2]);
            return false;

        // Code of other messages
        default:
            // Sending, that message was delivered
            sendWithoutApply(MES_APPL, {recieveData->data[1]});

            // Checking get data
            return getData();
        }
    }
    return false;
}

// Check, if lost connection from other side
bool Internet::checkDisconect() {
    // Check, if time for arrive is too much
    if (SDL_GetTicks64() > lastMessageArrive) {
        // Something wrong with connection
        showDisconect();

        // Stopping process
        return true;
    }
    // Nothing happen
    return false;
}


// Template for function for getting data
bool Internet::getData() {
    switch (recieveData->data[0]) {
    // Strange/unknown code
    default:
        return false;
    }
}
