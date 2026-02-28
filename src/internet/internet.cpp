/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdio>
#include "internet.hpp"


Internet::Internet()
: socket() {
    socket.tryBindTo(BASE_PORT);
    logAdditional("Internet created correctly");
}

void Internet::connectTo(const Destination& _dest) {
    // Add new connection
    reciepients.emplace_back(_dest);
    logAdditional("Connecting to %s:%u", _dest.getAddress(), _dest.getPort());
}

void Internet::detachOf(const sockaddr_in* _address) {
    // Delete connection
    for (int i=0; i < reciepients.size(); ++i) {
        if (reciepients[i].isAddress(_address)) {
            reciepients.erase(reciepients.begin()+i);
            logAdditional("Deleting connection to %d", i);
            return;
        }
    }
    logAdditional("Can't detach connection");
}

Uint16 Internet::getPort() const {
    return socket.getPort();
}

void Internet::close() {
    // Closing all reciepients
    reciepients.clear();
    logAdditional("Close all connections");
}

void Internet::disconnect() {
    // Sending message with quiting connection
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(socket, Message{ConnectionCode::Quit, Uint8(1)});
    }
    logAdditional("Disconnecting from games");
}

void Internet::checkResendMessages() {
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].checkResending(socket);
    }
}

void Internet::checkNeedApplyConnection() {
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].checkNeedApplyConnection(socket);
    }
}

bool Internet::checkStatus() {
    // Resetting flag
    disconnected = true;
    // Check all connections
    for (int i=0; i < reciepients.size(); ++i) {
        disconnected &= reciepients[i].checkDisconnect();
    }
    return disconnected;
}

void Internet::sendFirst(const Destination& _dest, const Message& _message) const {
    // Sending it here
    socket.send(_dest, _message);
}

void Internet::sendAll(const Message& _message) {
    // Sending it to all recipients
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendUnconfirmed(socket, _message);
    }
}

void Internet::sendAllConfirmed(const ConfirmedMessage& _message) {
    // Sending it to all reciepients
    for (int i=0; i < reciepients.size(); ++i) {
        reciepients[i].sendConfirmed(socket, _message);
    }
}

const GetPacket* Internet::getNewMessages() {
    // Try get message
    GetPacket* packet = socket.recieve();
    // Check, if get correct message
    if (packet && packet->isBytesAvaliable(2)) {
        // Get message source
        Reciepient* source = nullptr;
        for (int i=0; i < reciepients.size(); ++i) {
            if (reciepients[i].isAddress(packet->getSourceAddress())) {
                source = &reciepients[i];
                break;
            }
        }

        if (source) {
            // Logging get message
            logAdditional("Get message from %s, size %u, type: %u",
                source->getName(), packet->getLength(), packet->getData<Uint8>(0));

            // Update wait timer
            source->updateGetTimeout();

            // Getting index
            Uint8 index = packet->getData<Uint8>(1);

            // Checking get message on special types
            switch (packet->getData<ConnectionCode>(0)) {
            case ConnectionCode::Confirm:
                // Applying in sended array, that message was delivered
                source->applyMessage(index);
                break;

            case ConnectionCode::Null:
            case ConnectionCode::ApplyConnection:
                // Can be addtiotion to apply every connection

                // Sending message, applying that message was get
                source->sendUnconfirmed(socket, Message{Uint8(ConnectionCode::Confirm), index});
                break;

            default:
                // Sending message, applying that message was get
                source->sendUnconfirmed(socket, Message{Uint8(ConnectionCode::Confirm), index});

                // Check, if already get it
                if (source->checkIndexUniqness(index)) {
                    // In other cases - external updation
                    return packet;
                }
            }
            return nullptr;
        } else {
            // Logging get message
            logAdditional("Get unknown message, type %u, size %u", packet->getData<Uint8>(0), packet->getLength());
            // Special action, if address is unknown
            return packet;
        }
    }
    return nullptr;
}
