/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "message.hpp"


Uint8 Message::globalMessageIndex = 1;

void Message::resend(Connection& connection) {
    // Sending message itself
    connection.send(packet);

    // Resetting timer
    nextResend = getTime() + MESSAGE_RESEND_TIMEOUT;
}

void Message::checkNeedResend(Connection& _connection) {
    // Check, if get over timer
    if (getTime() > nextResend) {
        #if CHECK_ALL
        SDL_Log("Resending packet with code: %u, index: %u", packet.getData()[0], messageIndex);
        #endif
        resend(_connection);
    }
}

bool Message::applyMessage(Uint8 _index) {
    return messageIndex == _index;
}
