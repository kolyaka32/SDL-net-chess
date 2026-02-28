/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "confirmedMessage.hpp"


Uint8 ConfirmedMessage::globalMessageIndex = 1;

void ConfirmedMessage::updateGlobalIndex() {
    // Upating global message index, skipping 0
    if (globalMessageIndex == maxSendId) {
        globalMessageIndex = 1;
    } else {
        globalMessageIndex++;
    }
}

bool ConfirmedMessage::isNeedResend() {
    // Check, if get over timer
    if (getTime() > nextResend) {
        nextResend = getTime() + messageResendTimeout;
        logAdditional("Resending packet with code: %u, index: %u", getData()[0], messageIndex);
        return true;
    }
    return false;
}

bool ConfirmedMessage::applyMessage(Uint8 _index) const {
    return messageIndex == _index;
}
