/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <stdlib.h>

#include "internetServer.hpp"


// Creating server port
InternetServerCycle::InternetServerCycle() {
    // Openning UDP port to recieve data from client
    while ((socket = SDLNet_UDP_Open(serverPort)) == nullptr) {
        // Checking, if not open port - setting random
        serverPort = std::rand() % 4000;
    }

    // Simulated packet loss for packets for better testing
    #if DEBUG
    SDLNet_UDP_SetPacketLoss(socket, CONNECTION_LOST_PERCENT);
    #endif
}
