/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "message.hpp"


// Base class of internet library
class InternetLibrary {
 public:
    InternetLibrary();
    ~InternetLibrary();
};


// Base class for work with internet connection
class Internet : InternetLibrary, public MessageSender {
 protected:
    // Show message boxes functions
    void showDisconect();       // Function of showing accidential disconect
    void showStopConnection();  // Function of showing connection normal stop
    void showCantConnect();     // Function of showing message of problems with connection

 protected:
    // Data for internet work
    UDPpacket* recieveData;    // Packet to recieve data

    // Connection control system
    timer lastMessageArrive;   // Timer, when last message arrive to control connection

 protected:
    // Function for sending any data
    //void send(MESSAGE_types type, Uint8 d1 = 0, Uint8 d2 = 0, Uint8 d3 = 0, Uint8 d4 = 0);
    virtual Uint8 getData();       // Template for getting any codes from other side
    Uint8 update();                // Function for updating all states of

 public:
    Internet();
    ~Internet();
};
