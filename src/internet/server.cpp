/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <string>
#include <ctime>
#include "server.hpp"


Server::Server()
: Connection() {
    // Resetting basic connecting port
    currentPort = BASE_PORT;

    // Finding avalialble port
    srand(time(0));
    while ((gettingSocket = NET_CreateDatagramSocket(nullptr, currentPort)) == nullptr) {
        // Creating another random port
        currentPort = rand() % 10000;
    }

    #if CHECK_CORRECTION
    // Adding some packet loss for better testing
    NET_SimulateDatagramPacketLoss(gettingSocket, CONNECTION_LOST_PERCENT);
    SDL_Log("Server created: %u, address: %s, port: %u", gettingSocket, getLocalIP(), currentPort);
    #endif
}

Server::~Server() {
    #if CHECK_CORRECTION
    SDL_Log("Destroying server, closing net library");
    #endif

    // Clearing rest data
    NET_DestroyDatagramSocket(gettingSocket);
    if (sendAddress) {
       NET_UnrefAddress(sendAddress); 
    }

    // Closing new library
    NET_Quit();
}

Uint16 Server::getPort() {
    return currentPort;
}

void Server::connectToLastMessage() {
    // Can be additional checks on versions
    // Connecting to address from last message
    sendAddress = NET_RefAddress(recievedDatagram->addr);
    sendPort = recievedDatagram->port;
}
