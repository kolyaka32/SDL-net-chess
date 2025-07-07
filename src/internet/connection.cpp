/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <string>
#include "connection.hpp"


// Static class members for lobby/game unity
NET_DatagramSocket* Connection::gettingSocket;
NET_Datagram* Connection::recievedDatagram;
NET_Address* Connection::sendAddress;
Uint16 Connection::sendPort;


Connection::Connection() {}

void Connection::start() {
    // Intialasing internet library
    NET_Init();
    #if CHECK_CORRECTION
    // Extra clearing
    gettingSocket = nullptr;
    sendAddress = nullptr;
    sendPort = 0;
    #endif
    recievedDatagram = nullptr;
}

void Connection::stop() {
    // Destrying previous data
    if (recievedDatagram) {
        delete lastPacket;
        lastPacket = nullptr;
        NET_DestroyDatagram(recievedDatagram);
        recievedDatagram = nullptr;
    }

    // Closing new library
    NET_Quit();
}

ConnectionCode Connection::getCode() {
    // Destrying previous data
    if (recievedDatagram) {
        delete lastPacket;
        lastPacket = nullptr;
        NET_DestroyDatagram(recievedDatagram);
        recievedDatagram = nullptr;
    }

    // Getting new datagramm
    if (NET_ReceiveDatagram(gettingSocket, &recievedDatagram)) {
        // Check, if get any data
        if (recievedDatagram) {
            // Writing getted data for debug
            #if CHECK_CORRECTION
            SDL_Log("Get packet with %u bytes, from %s, port: %u", recievedDatagram->buflen, NET_GetAddressString(recievedDatagram->addr), recievedDatagram->port);
            for (int i=0; i < recievedDatagram->buflen; ++i) {
                SDL_Log("%u", recievedDatagram->buf[i]);
            }
            #endif
            // Updating get packet
            lastPacket = new GetPacket(recievedDatagram);
            return (ConnectionCode)lastPacket->getData<Uint8>();
        }
    }
    return ConnectionCode::Null;
}

const char* Connection::getLocalIP() {
    // Getting local addresses
    int addressesNumber = 0;
    NET_Address** addresses = NET_GetLocalAddresses(&addressesNumber);

    // Finding usedull address
    for (int i=0; i < addressesNumber; ++i) {
        const char* address = NET_GetAddressString(addresses[i]);
        bool usefull = true;
        // Check, if not IPv6 address
        for (const char* c = address; *c; ++c) {
            if (*c == ':') {
                usefull = false;
                break;
            }
        }
        // Check, if not basic '127.0.0.1'
        if (usefull && strcmp(address, "127.0.0.1")) {
            // Use this address
            return address;
        }
    }
    return nullptr;
}
