/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "destination.hpp"


#if ((USE_WINSOCK) || (USE_SOCKET))

Destination::Destination(const sockaddr_in* _address) {
    address = *_address;
}

Destination::Destination(const sockaddr* _address, int _size) {
    #if CHECK_CORRECTION
    if (_size != sizeof(address)) {
        logger.important("Size doesn't fit - wrong address type");
    }
    #endif
    memcpy(&address, _address, sizeof(address));
}

Destination::Destination(const char* _name, Uint16 _port) {
    // IP address, and port for the socket that is being bound.
    address.sin_family = AF_INET;  // IPv4
    address.sin_addr.s_addr = inet_addr(_name);
    address.sin_port = htons(_port);
}

bool Destination::operator==(const sockaddr_in* b) const {
    return address.sin_addr.s_addr == b->sin_addr.s_addr
        && address.sin_port == b->sin_port;
}

sockaddr* Destination::getAddress() const {
    return (sockaddr*)&address;
}

int Destination::getSize() const {
    return sizeof(address);
}

const char* Destination::getName() const {
    return inet_ntoa(address.sin_addr);
}

Uint16 Destination::getPort() const {
    return ntohs(address.sin_port);
}

#endif  // ((USE_WINSOCK) || (USE_SOCKET))
