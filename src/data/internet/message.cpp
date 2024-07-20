/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "message.hpp"


MessageSender::MessageSender() {
    // Resetting ID counter
    ID = 0;

    // Creating send packet
    sendData.maxlen = INTERNET_BUFFER;
}

MessageSender::~MessageSender() {
    // Clearing dynamic memory
    for (Uint8 i=0; i < confirmMessages.size(); ++i) {
        delete[] confirmMessages[i].data;
    }
    // Clearing rest messages
    confirmMessages.clear();
}

void MessageSender::send(Message& _message) {
    // Moving pointer with data to send packet
    sendData.data = _message.data;
    // Setting it size
    sendData.len = _message.size;

    // Sending by internet
    SDLNet_UDP_Send(socket, -1, &sendData);

    // Resetting it timer to next check
    _message.lastSended = SDL_GetTicks64() + MESSAGE_APPLY_TIMEOUT;

    // Resetting timer of last sended message
    lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL_TIMEOUT;
}

// Setting message with this id as applied
void MessageSender::applyMessage(Uint8 id) {
    // Searching for need id
    for (Uint8 i=0; i < confirmMessages.size(); ++i) {
        if (confirmMessages[i].data[1] == id) {
            // Clearing dynamic memory before deleting
            delete[] confirmMessages[i].data;

            // Need message applied and clear
            confirmMessages.erase(confirmMessages.begin() + i);
            return;
        }
    }
}

// Resend all messages, which wasn't applied
void MessageSender::checkNeedResend() {
    // Checking all messages for getting over timer
    for (Uint8 i=0; i < confirmMessages.size(); ++i) {
        if (confirmMessages[i].lastSended > SDL_GetTicks64()) {
            // Resending it
            send(confirmMessages[i]);
        }
    }
}
