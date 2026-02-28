/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "messages/getPacket.hpp"
#include "destination.hpp"


// Class for socket - object, from which send data and on which recieve it
// Also contains local address for it
class Socket {
 private:
    // Local internet address
    sockaddr_in localAddress;
    // Socket itself
    SocketType sck = -1;
    // Port at which socket is created
    Uint16 port;
    // Packet, with recieved data (if was)
    GetPacket packet;

 protected:
    // Trying set socket to "port", return 0-if can, 1 if port used, -1 on error
    int tryBind();
    void setNonBlockingMode();
    void setReuseAddressMode();
    void setBroadcastMode();

 public:
    // Created unspecified socket
    Socket();
    ~Socket();
    // Setting socket to use for recieving data at specified port (or another open)
    void tryBindTo(Uint16 port);
    // Bind to random port
    void tryBindTo();
    // Setting socket to recieve from whole subnet
    void setRecieveBroadcast();
    // Set special modes
    void setSendBroadcast();
    // Working with socket itself
    Uint16 getPort() const;
    void send(const Destination& dest, const Message& message) const;
    GetPacket* recieve();
};
