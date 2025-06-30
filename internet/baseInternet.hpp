/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "message.hpp"


// Base class for work with internet connection
class Internet : public MessageSender {
 protected:
    // Data for internet work
    UDPpacket* recieveData;    // Packet to recieve data
    timer lastMessageArrive;   // Timer, when last message arrive to control connection

    // Show message boxes functions
    void showDisconect();       // Function of showing accidential disconect
    void showStopConnection();  // Function of showing connection normal stop
    void showCantConnect();     // Function of showing message of problems with connection

    // Functions for connection update
    void checkSendTimeout();  // Check, if too much time since last message send
    bool checkGetMessage();   // Check, if get new message
    virtual bool getData();   // Template for getting any codes from other side
    bool checkDisconect();    // Check, if lost connection from other side

 public:
    Internet();
    ~Internet();
};
