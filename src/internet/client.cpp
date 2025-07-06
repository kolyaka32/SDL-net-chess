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
    sendAddress = recievedDatagram->addr;
    sendPort = recievedDatagram->port;
}

// Creating getting port
    //gettingSocket = NET_CreateDatagramSocket(0, 0);

    /*NET_Address* sendTo = NET_ResolveHostname("127.0.0.1");
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

    // Initialasing SDL net library
    //NET_Init();
    client.start();
}

ClientLobby::~ClientLobby() {
    //NET_DestroyDatagramSocket(gettingSocket);
    //NET_Quit();
}*/
