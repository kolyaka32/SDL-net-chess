/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseInternet.hpp"
#include "../../data/data.hpp"
#include "../../workCodes.hpp"


// Initialasing internet library
InternetLibrary::InternetLibrary() {
    // Initialising internet libarary
    if (SDLNet_Init()) {
        #if CHECK_CORRECTION
        SDL_Log("Couldn't initialise internet library: %s\n", SDLNet_GetError());
        exit(ERR_SDL_NET);
        #endif
    }
}

// Closing internet library
InternetLibrary::~InternetLibrary() {
    // Closing internet library
    SDLNet_Quit();
}


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
        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
        //    "Disconect", "Your connection lost, server disconect", data.window);
        break;

    case LNG_RUSSIAN:
        //SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
        //    "Соединение потеряно", "Соединение потерено, сервер отключён", data.window);
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

// Macros for sending message
/*void Internet::send(MESSAGE_types type, Uint8 d1, Uint8 d2, Uint8 d3, Uint8 d4) {
    sendData->data[0] = type;
    sendData->data[1] = d1;
    sendData->data[2] = d2;
    sendData->data[3] = d3;
    sendData->data[4] = d4;
    SDLNet_UDP_Send(socket, -1, sendData);

    lastMessageSend = SDL_GetTicks64();
    waitApply = true;
}*/

//
Uint8 Internet::update() {
    // Locking thread
    data.drawMutex.lock();

    // Checking, if need to send NULL-message
    if (SDL_GetTicks64() > lastMessageSend) {
        sendWithoutApply(MES_NONE);
    }

    // Checking, if messages wasn't delivered
    checkResend();
    
    // Checking if get new data
    if (SDLNet_UDP_Recv(socket, recieveData)) {
        // Sending, that message was applied
        sendWithoutApply(MES_APPL, {recieveData->data[1]});

        // Getting data
        if (getData()) {
            // Stopping after special commands
            // Unlocking thread
            data.drawMutex.unlock();
            return 1;
        }
        // Resetting arriving timer
        lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
    } else {
        // Check, if time for arrive is too much
        if (SDL_GetTicks64() > lastMessageArrive) {
            // Something wrong with connection
            showDisconect();

            // Unlocking thread
            data.drawMutex.unlock();
            return 1;
        }
    }
    // Unlocking thread
    data.drawMutex.unlock();
    
    // None return
    return 0;
}

// Template for function for getting data
Uint8 Internet::getData() {
    switch (recieveData->data[0]) {
    // Code of closing game - going to menu
    case MES_STOP:
        showStopConnection();
        return 1;

    // Code of applaying last message
    case MES_APPL:
        applyMessage(recieveData->data[1]);
        return 0;

    // Strange/unknown code
    default:
        return 0;
    }
}
