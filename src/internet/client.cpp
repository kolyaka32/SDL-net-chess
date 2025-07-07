/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "client.hpp"


void Client::start() {
    // Basic initialasing
    Connection::start();

    // Creating random recieving socket
    gettingSocket = NET_CreateDatagramSocket(nullptr, 0);

    #if CHECK_CORRECTION
    SDL_Log("Client created: %u, address: %s", gettingSocket, getLocalIP());
    #endif
}

void Client::stop() {
    // Clearing rest data
    NET_DestroyDatagramSocket(gettingSocket);
    NET_UnrefAddress(sendAddress);

    // Basic clearing
    Connection::stop();
}

void Client::tryConnect(const char* _address, Uint16 _port) {
    #if CHECK_CORRECTION
    SDL_Log("Trying connect to: address: %s, port: %u", _address, _port);
    #endif
    sendAddress = NET_ResolveHostname(_address);
    sendPort = _port;

    // Check, if address is incorrect
    if (sendAddress == nullptr) {
        #if CHECK_CORRECTION
        SDL_Log("Can't find this address");
        #endif
        return;
    }

    // Waiting, if get address
    NET_WaitUntilResolved(sendAddress, 20);

    // Check, if get address
    if (NET_GetAddressStatus(sendAddress) != 1) {
        #if CHECK_CORRECTION
        SDL_Log("Can't connect to this address");
        #endif
        return;
    }

    // Sending initialasing packet
    #if CHECK_CORRECTION
    SDL_Log("Sending initialasing packet");
    #endif
    send(ConnectionCode::Init);

    // Clearing temporary addresses
    NET_UnrefAddress(sendAddress);
}

void Client::connectToLastMessage() {
    // Connecting to address from last message
    sendAddress = NET_RefAddress(recievedDatagram->addr);
    sendPort = recievedDatagram->port;
}
