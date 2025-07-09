/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <utility>
#include "codes.hpp"
#include "../data/macroses.hpp"
#include "../define.hpp"
#include "../testing.hpp"


// Class with any ordered data
class Data {
protected:
    // Data, contained in this array
    Uint8* data;

    // Function for correct bits order to prevent wrong understanding
    template <typename T>
    T swapLE(T object);

public:
    Data() {};
};


// Class with data for sending somewhere
class SendPacket : public Data {
private:
    int length;

protected:
    // Functions for converting data to raw array
    template <typename T>
    void write(int offset, T object);
    template <typename T, typename ...Args>
    void write(int offset, T object, Args&& ...args);

public:
    template <typename ...Args>
    SendPacket(Args ...args);
    ~SendPacket();
    Uint8* getData();
    int getLength();
};


// Class with getted data from somewhere
class GetPacket : public Data {
private:
    int offset = 0;
    // Additional errors checks
    #if CHECK_CORRECTION
    int size;
    #endif

public:
    GetPacket(NET_Datagram* datagramm);
    // Functions for get data from message by order
    template <typename T>
    T getData();
    // Functions for get data from message at specified position
    template <typename T>
    T getData(int offset);
};


template <typename ...Args>
SendPacket::SendPacket(Args ...args) {
    // Getting length as sum of all sizes of arguments
    length = sizeof...(args);

    // Creating array for data
    data = new Uint8[length];

    write(0, args...);
}

template <typename T>
void SendPacket::write(int _offset, T _object) {
    *(data + _offset) = swapLE<T>(_object);
}

template <typename T, typename ...Args>
void SendPacket::write(int _offset, T _object, Args&& ...args) {
    // Writing current object
    *(data + _offset) = swapLE<T>(_object);
    write(_offset + sizeof(T), args...);
}

template <typename T>
T GetPacket::getData() {
    #if CHECK_CORRECTION
    if (offset + sizeof(T) > size) {
        throw "Can't read data - not enogh length";
    }
    #endif

    // Moving caret for reading next object correct
    offset += sizeof(T);
    return swapLE<T>((T)(*(data + offset - sizeof(T))));
}

template <typename T>
T GetPacket::getData(int _offset) {
    #if CHECK_CORRECTION
    if (_offset + sizeof(T) > size) {
        throw "Can't read data - not enogh length";
    }
    #endif
    return swapLE<T>((T)(*(data + _offset)));
}
