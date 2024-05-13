#pragma once

#include <vector>
#include <initializer_list>

#include "message.hpp"


// Base class of internet library
class InternetLibrary
{
public:
    InternetLibrary();
    ~InternetLibrary();
};


// Base class for work with internet connection
class Internet : InternetLibrary
{
protected:
    // Data for internet work
    UDPsocket socket;          // Socket to send/recieve data
    UDPpacket* sendData;       // Packet to send data
    UDPpacket* recieveData;    // Packet to recieve data

    // Connection control system
    timer lastMessageArrive;   // Timer, when last message arrive to control connection
    timer lastMessageSend;     // Timer, when last message send to control connection
    bool waitApply;            // Flag of waiting apply message

    // External messages
    void showDisconect();       // Function of showing accidential disconect
    void showStopConnection();  // Function of showing connection normal stop
    void showCantConnect();     // Function of showing message of problems with connection

protected:
    // Function for sending any data
    void send(MESSAGE_types type, Uint8 d1 = 0, Uint8 d2 = 0, Uint8 d3 = 0, Uint8 d4 = 0);
    virtual Uint8 getData();       // Template for getting any codes from other side
    Uint8 update();                // Function for updating all states of 

public:
    Internet();
    ~Internet();
};
