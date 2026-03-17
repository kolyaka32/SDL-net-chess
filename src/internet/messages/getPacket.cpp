/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "getPacket.hpp"


GetPacket* GetPacket::tryGetData(const SocketType _socket) {
    // Try recieve data
    srcAddressLength = sizeof(srcAddress);
    length = recvfrom(_socket, buffer, sizeof(buffer), 0, (sockaddr*)&srcAddress, &srcAddressLength);
    if (length > 0) {
        logger.additional("Get data with length: %d, type: %d", length, buffer[0]);
        return this;
    }
    return nullptr;
}

const sockaddr_in* GetPacket::getSourceAddress() const {
    return &srcAddress;
}

int GetPacket::getSourceAddressLength() const {
    return srcAddressLength;
}

bool GetPacket::isBytesAvaliable(int bytes) const {
    return length >= bytes;
}

int GetPacket::getLength() const {
    return length;
}

const void* GetPacket::getPointer(int _offset) const {
    return buffer + _offset;
}
