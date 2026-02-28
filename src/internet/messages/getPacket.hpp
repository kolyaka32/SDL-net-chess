/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../library.hpp"


// Class with getted data from somewhere
class GetPacket {
 private:
    // Address, from which
    sockaddr_in srcAddress;
    socklen_t srcAddressLength;
    // Data, contained in this array
    char buffer[100];
    int length = 0;

 public:
    // Trying get new data from specified socket
    GetPacket* tryGetData(const SocketType winSocket);

    // Working with get data
    const sockaddr_in* getSourceAddress() const;
    int getSourceAddressLength() const;
    // Function for check, if has enought bytes to read
    bool isBytesAvaliable(int bytes) const;
    // Returns length of getted data
    int getLength() const;
    // Functions for get data from message at specified position
    template <typename T>
    T getData(int offset) const;
    const void* getPointer() const;
};


template <typename T>
T GetPacket::getData(int _offset) const {
    #if (CHECK_CORRECTION)
    if (_offset + sizeof(T) > length) {
        logImportant("Can't read data - not enogh length");
    }
    #endif
    return readNet((T)(buffer[_offset]));
}
