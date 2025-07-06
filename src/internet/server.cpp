/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <string>
#include <ctime>
#include "server.hpp"


Uint16 Server::currentPort;


void Server::start() {
    // Basic initialasing
    Connection::start();

    // Resetting basic connecting port
    currentPort = 8000;

    // Finding avalialble port
    srand(time(0));
    while ((gettingSocket = NET_CreateDatagramSocket(nullptr, currentPort)) == nullptr) {
        // Creating another random port
        currentPort = rand() % 10000;
    }

    #if CHECK_CORRECTION
    SDL_Log("Server created: %u, address: %s, port: %u", gettingSocket, getLocalIP(), currentPort);
    #endif
}

void Server::stop() {
    // Clearing rest data
    NET_DestroyDatagramSocket(gettingSocket);

    // Basic clearing
    Connection::stop();
}

Uint16 Server::getPort() {
    return currentPort;
}

void Server::connectToLastMessage() {
    // Can be additional checks on versions
    // Connecting to address from last message
    sendAddress = recievedDatagram->addr;
    sendPort = recievedDatagram->port;

    // Sending applroving message
    send(ConnectionCode::Init);
}
