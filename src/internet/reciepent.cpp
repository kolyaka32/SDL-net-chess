/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "reciepient.hpp"


Reciepient::Reciepient(const Destination& _dest)
: dest(_dest) {}

Reciepient::Reciepient(const Reciepient& _object)
: dest(_object.dest),
needResendApplyConnection(_object.needResendApplyConnection),
wasDisconected(_object.wasDisconected),
unconfirmedMessages(_object.unconfirmedMessages),
getIndexes(_object.getIndexes) {}

Reciepient::Reciepient(Reciepient&& _object) noexcept
: dest(std::move(_object.dest)),
needResendApplyConnection(_object.needResendApplyConnection),
wasDisconected(_object.wasDisconected),
unconfirmedMessages(std::move(_object.unconfirmedMessages)),
getIndexes(std::move(_object.getIndexes)) {}

Reciepient& Reciepient::operator=(Reciepient&& _object) noexcept {
    dest = std::move(_object.dest);
    needResendApplyConnection = _object.needResendApplyConnection,
    wasDisconected = _object.wasDisconected,
    unconfirmedMessages = _object.unconfirmedMessages,
    getIndexes = std::move(_object.getIndexes);
    return *this;
}

void Reciepient::sendConfirmed(const Socket& _socket, const ConfirmedMessage& _message) {
    // Firstly sending it
    sendUnconfirmed(_socket, _message);
    // Adding to list to check status
    unconfirmedMessages.push_back(_message);
}

void Reciepient::sendUnconfirmed(const Socket& _socket, const Message& _message) {
    // Sending it
    _socket.send(dest, _message);
    // Updating send timer
    needResendApplyConnection = getTime() + messageApplyTimeout;
}

void Reciepient::checkResending(const Socket& _socket) {
    // Check if client connected
    if (getTime() < wasDisconected) {
        for (int i=0; i < unconfirmedMessages.size(); ++i) {
            if (unconfirmedMessages[i].isNeedResend()) {
                // Resending message
                sendUnconfirmed(_socket, unconfirmedMessages[i]);
            }
        }
    }
}

bool Reciepient::checkDisconnect() {
    return getTime() > wasDisconected;
}

void Reciepient::checkNeedApplyConnection(const Socket& _socket) {
    // Check if client connected and need to apply connection
    if (getTime() < wasDisconected && getTime() > needResendApplyConnection) {
        sendConfirmed(_socket, ConfirmedMessage{ConnectionCode::ApplyConnection});
    }
}

bool Reciepient::isAddress(const sockaddr_in* _dest) {
    return dest == _dest;
}

void Reciepient::updateGetTimeout() {
    wasDisconected = getTime() + connectionGetTimeout;
}

void Reciepient::applyMessage(Uint8 _index) {
    // Appling getting message
    logAdditional("Appling, that message with index %u was delivered", _index);

    // Find that message
    for (int i=0; i < unconfirmedMessages.size(); ++i) {
        if (unconfirmedMessages[i].applyMessage(_index)) {
            // Delete it from list
            unconfirmedMessages.erase(unconfirmedMessages.begin() + i);
            break;
        }
    }
}

bool Reciepient::checkIndexUniqness(Uint8 _index) {
    return getIndexes.isUnique(_index);
}

const char* Reciepient::getName() const {
    return dest.getName();
}
