/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"
#include "../data/time.hpp"


// Message, waiting for applying of getting
class Message {
private:
    timer nextResend;    // Time, when need to resend message
    static Uint8 globalMessageIndex;
    Uint8 messageIndex;  // Index to check applying and getting messages
    SendPacket packet;

protected:
    void resend(Connection& connection);

public:
    template <typename ...Args>
    Message(Connection& connection, ConnectionCode code, Args&& ...args);
    void checkNeedResend(Connection& connection);
    bool applyMessage(Uint8 index);  // Check, if that message arrived and need to clearing
};

template <typename ...Args>
Message::Message(Connection& _connection, ConnectionCode _code, Args&& ...args)
: messageIndex(globalMessageIndex),
packet(Uint8(_code), messageIndex, args...) {
    #if CHECK_CORRECTION
    SDL_Log("Firstly sending message with code: %u, index: %u", (Uint8)_code, messageIndex);
    #endif
    // Firstly sending message
    resend(_connection);

    // Upating global message index, skipping 0
    if (globalMessageIndex == 127) {
        globalMessageIndex = 1;
    } else {
        globalMessageIndex++;
    }
}
