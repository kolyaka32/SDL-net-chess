/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverData.hpp"
#include "../data/macroses.hpp"


ServerData::ServerData(const sockaddr_in* _address, int _ping)
: ping(min(_ping, 0)),
dest(_address) {}

int ServerData::getPing() const {
    return ping;
}

const Destination& ServerData::getAddress() const {
    return dest;
}
