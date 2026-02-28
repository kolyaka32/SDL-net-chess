/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "socket.hpp"


Socket::Socket() {
    // Create a socket for listening for incoming connection requests.
    sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    #if (USE_WINSOCK)
    sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sck == INVALID_SOCKET) {
        logAdditional("Can't create socket with error: %d", getError);
    }
    #endif
    #if (USE_SOCKET)
    if (sck == -1) {
        logAdditional("Can't create socket with error: %d", getError);
    }
    #endif
    // Setting local address
    localAddress.sin_family = AF_INET;
    localAddress.sin_addr.s_addr = INADDR_ANY;
    // Setting to non-blocking mode
    setNonBlockingMode();
}

Socket::~Socket() {
    #if (USE_WINSOCK)
    if (closesocket(sck) == SOCKET_ERROR) {
        logImportant("Close socket function failed with error %d", getError);
    }
    #endif
    #if (USE_SOCKET)
    close(sck);
    #endif
}

int Socket::tryBind() {
    // Setting and remembering port
    localAddress.sin_port = htons(port);

    // Trying bind address to socket
    if (bind(sck, (sockaddr*)&localAddress, sizeof(localAddress))) {
        #if (USE_WINSOCK)
        if (getError == WSAEADDRINUSE) {
            return 1;
        }
        #endif
        #if (USE_SOCKET)
        if (getError == EADDRINUSE) {
            return 1;
        }
        #endif
        return -1;
    }
    return 0;
}

void Socket::setNonBlockingMode() {
    // Setting socket to non-blocking mode
    #if (USE_WINSOCK)
    DWORD nonBlocking = 1;
    if (ioctlsocket(sck, FIONBIO, &nonBlocking) != 0) {
        logImportant("Can't set socket to non-blocking mode: %d", getError);
    }
    #endif
    #if (USE_SOCKET)
    int value = 1;
    if (ioctl(sck, FIONBIO, &value) == -1) {
        logImportant("Can't set socket to non-blocking mode: %d", getError);
    }
    #endif
}

void Socket::setReuseAddressMode() {
    // Setting socket to allow to reuse address
    #if (USE_WINSOCK)
    bool value = true;
    #elif (USE_SOCKET)
    int value = 1;
    #endif
    if (setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value))) {
        logImportant("Can't set reusing socket, error: %d", getError);
    }
}

void Socket::setBroadcastMode() {
    // Setting socket to broadcast
    #if (USE_WINSOCK)
    bool value = true;
    #elif (USE_SOCKET)
    int value = 1;
    #endif
    if (setsockopt(sck, SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value))) {
        logImportant("Can't set socket to broadcast: %d", getError);
    }
}

void Socket::tryBindTo(Uint16 _port) {
    // Setting basic port
    port = _port;
    // Setting random seed from time
    SDL_srand(0);
    // Finding avaliable port
    // Setting socket to send from created local host (as back address)
    while (int result = tryBind()) {
        // Check, if port already using
        if (result > 0) {
            // Finding another port
            port = SDL_rand(40000) + 1500;
        } else {
            logImportant("Bind function failed with error %d", getError);
            return;
        }
    }
    logAdditional("Openned socket at port %d", port);
}

void Socket::tryBindTo() {
    // Setting random seed from time
    SDL_srand(0);
    tryBindTo(SDL_rand(40000) + 1500);
}

void Socket::setRecieveBroadcast() {
    // Set, that any app could use that port (for many apps run simultaneously)
    setReuseAddressMode();
    // Setting basic port for broadcast
    port = BROADCAST_PORT;
    // Tring to set this port to use
    if (tryBind()) {
        logImportant("Brodcast bind function failed with error %d", getError);
    }
    logAdditional("Openned broadcast socket at port %d", port);
}

void Socket::setSendBroadcast() {
    // Setting random seed from time
    SDL_srand(0);
    // Setting at random port
    tryBindTo(SDL_rand(40000) + 1500);
    // Setting to allow send broadcast messages
    setBroadcastMode();
}

void Socket::send(const Destination& _dest, const Message& _message) const {
    int sendLength = sendto(sck, _message.getData(), _message.getLength(), 0, _dest.getAddress(), _dest.getSize());
    #if (CHECK_CORRECTION)
    if (sendLength != _message.getLength()) {
        logImportant("Don't send data correct, error: %d", getError);
    } else {
        logAdditional("Send sucsesfull: %d", _message.getLength());
    }
    #endif
}

Uint16 Socket::getPort() const {
    return port;
}

GetPacket* Socket::recieve() {
    return packet.tryGetData(sck);
}
