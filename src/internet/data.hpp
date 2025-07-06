/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_net/SDL_net.h>
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
protected:
    // Functions for converting data to raw array
    template <typename T, typename ...Args>
    void write(T object, Args&& ...args);

public:
    template <typename ...Args>
    SendPacket(Args&& ...args);
    ~SendPacket();
    Uint8* getData();
    int getLength();
};


// Class with getted data from somewhere
class GetPacket : public Data {
private:
    int offset = 0;

public:
    GetPacket(NET_Datagram* datagramm);
    // Functions for get data from message by order
    template <typename T>
    T getData();
    // Functions for get data from message at specified position
    template <typename T>
    T getData(int offset);
};
