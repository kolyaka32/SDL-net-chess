/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameConnection.hpp"


GameConnection::GameConnection(const Connection& _connection)
: Connection(_connection) {
    #if CHECK_CORRECTION
    SDL_Log("Created internet game connection, sending to: %s:%u", NET_GetAddressString(sendAddress), sendPort);
    #endif
}

GameConnection::~GameConnection() {
    // Destrying previous data
    if (recievedDatagram) {
        delete lastPacket;
        lastPacket = nullptr;
        NET_DestroyDatagram(recievedDatagram);
        recievedDatagram = nullptr;
    }
    // NOT clearing address
}
