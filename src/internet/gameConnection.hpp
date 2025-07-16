/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "message.hpp"
#include "indexesArray.cpp"


class GameConnection : public Connection {
private:
    timer needResendApplyConnection;  // Time, after which need resend apply connection message
    timer needDisconect;              // Time, after which connection will be recognized as disconected
    std::vector<Message*> unconfirmedMessages;
    IndexesArray<10> getIndexes;
    bool disconnected = false;

protected:
    void checkReconnecting();
    void checkConnectionStatus();
    void checkNeedApplyConnection();
    void checkNeedResending();
    ConnectionCode checkNewMessage();

public:
    GameConnection(const Connection& connection);
    ~GameConnection();
    ConnectionCode updateMessages();
    template <typename ...Args>
    void sendConfirmed(ConnectionCode code, Args&& ...args);
    void tryReconnect();
};

template <typename ...Args>
void GameConnection::sendConfirmed(ConnectionCode _code, Args&& ...args) {
    // Adding new message to confirme array and send it
    Message* newMessage = new Message{*this, _code, args...};
    unconfirmedMessages.push_back(newMessage);
    // Updating timer
    needResendApplyConnection = getTime() + MESSAGE_APPLY_TIMEOUT;
}
