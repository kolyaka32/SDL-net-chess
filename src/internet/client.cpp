/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "client.hpp"


Client::Client()
: Connection() {
    // Creating random recieving socket
    gettingSocket = NET_CreateDatagramSocket(nullptr, 0);

    #if CHECK_CORRECTION
    // Adding some packet loss for better testing
    NET_SimulateDatagramPacketLoss(gettingSocket, CONNECTION_LOST_PERCENT);
    SDL_Log("Client created: %u, address: %s", gettingSocket, getLocalIP());
    #endif
}

Client::~Client() {
    #if CHECK_CORRECTION
    SDL_Log("Destroying client, closing net library");
    #endif

    // Clearing rest data
    NET_DestroyDatagramSocket(gettingSocket);
    if (sendAddress) {
       NET_UnrefAddress(sendAddress); 
    }

    // Closing new library
    NET_Quit();
}

void Client::tryConnect(const char* _address, Uint16 _port) {
    #if CHECK_CORRECTION
    SDL_Log("Trying connect to: address: %s, port: %u", _address, _port);
    #endif
    sendAddress = NET_ResolveHostname(_address);
    sendPort = _port;

    // Check, if address is incorrect
    if (sendAddress == nullptr) {
        #if CHECK_ALL
        SDL_Log("Can't find this address");
        #endif
        return;
    }

    // Waiting, if get address
    NET_WaitUntilResolved(sendAddress, 20);

    // Check, if get address
    if (NET_GetAddressStatus(sendAddress) != 1) {
        #if CHECK_ALL
        SDL_Log("Can't connect to this address");
        #endif
        return;
    }

    #if CHECK_ALL
    SDL_Log("Sending initialasing packet");
    #endif
    // Sending some initialasing packet (for more chances)
    send(ConnectionCode::Init, 0);
    send(ConnectionCode::Init, 0);
    send(ConnectionCode::Init, 0);

    // Clearing temporary addresses
    NET_UnrefAddress(sendAddress);
    sendAddress = nullptr;
}

void Client::connectToLastMessage() {
    // Connecting to address from last message
    sendAddress = NET_RefAddress(recievedDatagram->addr);
    sendPort = recievedDatagram->port;
}
