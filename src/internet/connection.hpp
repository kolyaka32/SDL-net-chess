/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "codes.hpp"
#include "data.hpp"


// Basic class for internet connection
class Connection {
protected:
    // Getting part
    static NET_DatagramSocket* gettingSocket;
    static NET_Datagram* recievedDatagram;

    // Sending part
    static NET_Address* sendAddress;
    static Uint16 sendPort;

public:
    Connection();
    void start();
    void stop();
    // Templated function for send any order of data
    template <typename ...Args>
    void send(ConnectionCode code, Args&& ...args);
    // Function for recieve new packets and update packets
    ConnectionCode getCode();
    // Packet with last getted data
    GetPacket* lastPacket = nullptr;

    // Function for get local IP address in IPv4 format
    static const char* getLocalIP();
};


// Sending function realisation (as templated)
template <typename ...Args>
void Connection::send(ConnectionCode code, Args&& ...args) {
    #if CHECK_CORRECTION
    if (sendAddress == nullptr || sendPort == 0) {
        SDL_Log("Can't send packet at unspecified address");
    }
    #endif
    // Creating new send packet
    SendPacket packet((Uint8)code, std::forward<Args>(args)...);
    // Sending it
    NET_SendDatagram(gettingSocket, sendAddress, sendPort, packet.getData(), packet.getLength());
    // Destrying packet
}
