/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "socket.hpp"


// Basic class for internet connection
class Reciepient {
 private:
    // Address, where send to or recieve from
    Destination dest;
    // System for confirmation of connection
    timer needResendApplyConnection = 0;             // Time, after which need resend apply connection message
    static const timer messageApplyTimeout = 2000;   // Time to send apply message to keep connecion
    timer wasDisconected = 0;                        // Time, after which connection will be recognized as disconected
    static const timer connectionGetTimeout = 6000;  // Time, after which connection is considered lost
    // Array of messages, waiting for apply from connection, or resend if don't
    std::vector<ConfirmedMessage> unconfirmedMessages;
    // Array of indexes of last getted messages
    IndexesArray<10> getIndexes;

 public:
    Reciepient(const Destination& dest);
    Reciepient(const Reciepient& object);
    Reciepient(Reciepient&& object) noexcept;
    Reciepient& operator=(Reciepient&& object) noexcept;

    // Send part
    void sendConfirmed(const Socket& socket, const ConfirmedMessage& message);
    void sendUnconfirmed(const Socket& socket, const Message& message);

    // Check part
    void checkResending(const Socket& socket);
    bool checkDisconnect();
    void checkNeedApplyConnection(const Socket& socket);
    bool isAddress(const sockaddr_in* dest);
    void updateGetTimeout();
    void applyMessage(Uint8 index);
    bool checkIndexUniqness(Uint8 index);
    const char* getName() const;
};
