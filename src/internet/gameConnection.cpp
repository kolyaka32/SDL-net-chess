/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "gameConnection.hpp"
#include "../data/cycleTemplate.hpp"
#include "../game/messageBox.hpp"


GameConnection::GameConnection(const Connection& _connection)
: Connection(_connection) {
    // Resetting timers
    needResendApplyConnection = getTime();
    needDisconect = getTime() + MESSAGE_GET_TIMEOUT;
    #if CHECK_CORRECTION
    SDL_Log("Created internet game connection, sending to: %s:%u", NET_GetAddressString(sendAddress), sendPort);
    #endif
}

GameConnection::~GameConnection() {
    // Checking on game restart
    if (!App::isRestarted()) {
        #if CHECK_CORRECTION
        SDL_Log("Destroying game connection");
        #endif
        // Sending message with quiting connection
        send(ConnectionCode::Quit);

        // Clearing rest messages
        for (int i=0; i < unconfirmedMessages.size(); ++i) {
            delete unconfirmedMessages[i];
        }
    }
}

ConnectionCode GameConnection::updateMessages() {
    checkConnectionStatus();
    checkNeedApplyConnection();
    checkNeedResending();
    return checkNewMessage();
}

void GameConnection::checkConnectionStatus() {
    // Check, if getting over timer
    if (getTime() > needDisconect) {
        // Disconneting, as lost connection
        #if CHECK_CORRECTION
        SDL_Log("Connection lost");
        #endif
        // Stopping current cycle
        CycleTemplate::stop();

        // Show message of disconect
        MessageBox::activate(1);
        return;
    }
}

void GameConnection::checkNeedApplyConnection() {
    if (getTime() > needResendApplyConnection) {
        // Sending new message which keep connection
        sendConfirmed(ConnectionCode::ApplyConnection);
    }
}

void GameConnection::checkNeedResending() {
    for (int i=0; i < unconfirmedMessages.size(); ++i) {
        unconfirmedMessages[i]->checkNeedResend(*this);
    }
}

ConnectionCode GameConnection::checkNewMessage() {
    // Checking, if get messages
    ConnectionCode code = getCode();
    if (code == ConnectionCode::Null) {
        return ConnectionCode::Null;
    }
    // Updating timer of last get message
    needDisconect = getTime() + MESSAGE_GET_TIMEOUT;

    // Writing getted data for debug
    #if CHECK_CORRECTION
    if (recievedDatagram->buflen > 1) {
        SDL_Log("Get packet with %u bytes, from %s, port: %u, code: %u, index: %u", recievedDatagram->buflen, NET_GetAddressString(recievedDatagram->addr), recievedDatagram->port, (Uint8)code, lastPacket->getData<Uint8>(1));
    } else {
        SDL_Log("Get 1 byte, from %s, port: %u, code: %u", NET_GetAddressString(recievedDatagram->addr), (Uint8)recievedDatagram->port, code);
    }
    #endif

    // Checking get message on type
    switch (code) {
    case ConnectionCode::Quit:
        // Connection forced terminatted
        #if CHECK_CORRECTION
        SDL_Log("Connection terminatted");
        #endif
        // Stopping current cycle
        CycleTemplate::stop();

        // Show message of disconect
        MessageBox::activate(2);
        return ConnectionCode::Null;

    case ConnectionCode::Confirm:
        {
            // Applying index of getted message
            Uint8 index = lastPacket->getData<Uint8>();

            // Applying in sended array, that message was delivered
            for (int i=0; i < unconfirmedMessages.size(); ++i) {
                if (unconfirmedMessages[i]->applyMessage(index)) {
                    delete unconfirmedMessages[i];
                    unconfirmedMessages.erase(unconfirmedMessages.begin() + i);
                    break;
                }
            }
        }
        return ConnectionCode::Null;

    case ConnectionCode::Init:
    case ConnectionCode::ApplyConnection:
        // Actioning like normal code
        code = ConnectionCode::Null;

    default:
        {
            // Check, if message was alredy gotten
            Uint8 index = lastPacket->getData<Uint8>();
            // Sending message, applying that message was get
            send(ConnectionCode::Confirm, index);
            // Updating timer
            needResendApplyConnection = getTime() + MESSAGE_APPLY_TIMEOUT;
            // Check, if need any additional actions with this code
            if (getIndexes.isUnique(index)) {
                // Adding to list for next checks
                getIndexes.add(index);
                // In other cases - external updation
                return code;
            }
            return ConnectionCode::Null;
        }
    }
}
