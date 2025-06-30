/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <initializer_list>
#include <SDL3_net/SDL3_net.h>

//#include "../../dataTypes.hpp"
//#include "../../define.hpp"

// Types of internet messages
enum MESSAGE_types{
    MES_NONE,   // Type of nothing for reset connection timer
    MES_INIT,   // Type of starting server and checking compatibility
    MES_START,  // Type of starting new round showing which player start
    MES_TURN,   // Type of setting shape on field, sending to opponent
    MES_STOP,   // Type of closing game and go to menu
    MES_REST,   // Type of restarting game and waiting for new start
    MES_APPL,   // Type of applying, that last message was get
    MES_SKIP,   // Type of skipping current round
};


// Type of data for save message data
struct Message {
    byte* data;  // Message data
    Uint8 size;  // Size of this data
    timer lastSended;  // Timer, when message was lastly send
};


// Class for send messages
class MessageSender {
 private:
    // Vector with all sended messages, which must be confirm
    std::vector<Message> confirmMessages;

    // Global id counter for control sended messages
    Uint8 ID;

    // Function for send need message
    void send(Message& message);

 protected:
    // Data for internet work
    UDPsocket socket;       // Socket to send/recieve data
    UDPpacket sendData;     // Packet to send data
    timer lastMessageSend;  // Timer, when last message send to control connection

    void applyMessage(Uint8 id);  // Setting message with this id as applied
    void checkNeedResend();       // Function for check, if need resend any of the messages

 public:
    MessageSender();
    ~MessageSender();

    // Function for create and send new message
    template <typename T = Uint8>
    void sendNew(const MESSAGE_types type = MES_NONE,
        const std::initializer_list<T> list = {});

    // Function for create and send new message without appliying it after
    template <typename T = Uint8>
    void sendWithoutApply(const MESSAGE_types type = MES_NONE,
        const std::initializer_list<T> list = {});
};


// Function for send data with need type and size
template <typename T>
void MessageSender::sendNew(const MESSAGE_types _type, const std::initializer_list<T> _list) {
    // Check, if can't get this message
    if (_list.size() * sizeof(T) + 2 > INTERNET_BUFFER) {
        // Show, that function incorrect
        throw "Wrong size of sended message";
    }
    // Creating send packet
    confirmMessages.push_back(Message());

    // Getting new message link for easyier acess
    Message& current = confirmMessages.back();

    // Setting it size
    current.size = _list.size() * sizeof(T) + 2;

    // Creating send data
    current.data = new byte[current.size];

    // Setting type of send message
    current.data[0] = _type;

    // Setting ID of message to confirm at return
    current.data[1] = ID;
    // Changing ID
    ID = (ID + 1) % MAX_SEND_ID;

    // Check, if need copy data
    if (current.size > 2) {
        memcpy(current.data + 2, _list.begin(), current.size);
    }

    // Sending this message
    send(current);
}

// Function for send data with need type and size without applying after
template <typename T>
void MessageSender::sendWithoutApply(const MESSAGE_types _type,
    const std::initializer_list<T> _list) {
    // Check, if can't get this message
    if (_list.size() * sizeof(T) + 2 > INTERNET_BUFFER) {
        // Show, that function incorrect
        throw "Wrong size of sended message";
    }
    // Creating send message
    Message current;

    // Setting it size
    current.size = _list.size() * sizeof(T) + 2;

    // Creating send data
    current.data = new byte[current.size];

    // Setting type of send message
    current.data[0] = _type;

    // Setting ID of message to confirm at return
    current.data[1] = ID;

    // Changin ID to next
    ID = (ID + 1) % MAX_SEND_ID;

    // Check, if need copy data
    if (current.size > 2) {
        memcpy(current.data + 2, _list.begin(), current.size);
    }

    // Sending this message
    send(current);

    // Clearing rest data
    delete[] current.data;
}
