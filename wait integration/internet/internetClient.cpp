/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <string>

#include "internetClient.hpp"


// Client part
//
InternetClientCycle::InternetClientCycle() {
    // Creating socket to get data
    socket = SDLNet_UDP_Open(0);

    // Simulated packet loss for packets for better testing
    #if DEBUG
    SDLNet_UDP_SetPacketLoss(socket, CONNECTION_LOST_PERCENT);
    #endif
}

//
InternetClientCycle::~InternetClientCycle() {}

//
Uint8 InternetClientCycle::tryConnect(const char* ipText, const char* portText) {
    IPaddress sendIP;  // IP of reciever
    if (SDLNet_ResolveHost(&sendIP, ipText, std::stoi(portText)) == 0) {
        // Setting send address
        sendData.address = sendIP;

        // Creating socket set to search for new messages
        SDLNet_SocketSet set = SDLNet_AllocSocketSet(1);
        SDLNet_UDP_AddSocket(set, socket);

        // Try send activation code at specifed coordinats
        sendNew(MES_INIT);
    }
    // Can't resolve this host
    return 0;
}
