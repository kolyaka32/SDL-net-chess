#pragma once

#include <SDL_net.h>

#include "../../dataTypes.hpp"
#include "../../define.hpp"

// Types of internet messages
enum MESSAGE_types{
    MES_NONE = 0,   // Type of nothing for reset connection timer
    MES_INIT = 1,   // Type of starting server and checking compatibility
    MES_START = 2,  // Type of starting new round showing which player start
    MES_TURN = 3,   // Type of setting shape on field, sending to opponent
    MES_STOP = 4,   // Type of closing game and go to menu
    MES_REST = 5,   // Type of restarting game and waiting for new start
    MES_APPL = 6,   // Type of applying, that last message was get
    MES_SKIP = 7,   // Type of skipping current round
};

// Class of internet messages to send and recieve
/*class Message
{
private:
    // Message data
    const MESSAGE_types type;  // Type of message
    const byte data[INTERNET_BUFFER];  // Data to send

    // Data for control sending
    timer lastSended;  // Timer, when message was lastly send
public:
    Message(const MESSAGE_types type = MES_NONE);
    ~Message();
    void send(UDPpacket* packet);  // Function of setting data to send
    const bool checkTime() const;

    friend class BaseInternet;  // Making data acessesable for sending
};
*/